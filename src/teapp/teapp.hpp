#pragma once

#include <functional>
#include <memory>
#include <pugixml.hpp>
#include <map>
#include <queue>
#include <format>
#include <spdlog/spdlog.h> 
#include <spdlog/sinks/rotating_file_sink.h>

// Renders doc as HTML to ncurses screen
// Note: HTML doc semantics may be tested at:
// https://www.w3schools.com/html/tryit.asp?filename=tryhtml_intro
void render(const pugi::xml_document &doc) {

  // Parse the HTML-like structure
  pugi::xml_node html = doc.child("html");
  pugi::xml_node body = html.child("body");

  int current_y = 1; // Start from row 1 to leave space for the top border
  int num_divs = 0;

  // Loop through divs directly and render them in sections
  for (auto const &div : body.children("div")) {
    // Render the content of the div inside the windows
    const std::string text = div.text().as_string();
    num_divs++;
  }
}

namespace tea {
    template <typename Msg>
    using IsQuit = std::function<bool(Msg)>;
  
    // Event is a key-value-pair
    using Event = std::map<std::string,std::string>;

    template <typename Msg>
    struct Html_Msg {
        pugi::xml_document doc{};
        std::map<std::string,std::function<std::optional<Msg>(Event)>> event_handlers{};
    };

    template <typename Model, typename Msg> class App {
    public:
      using Cmd = std::function<std::optional<Msg>()>;
      using Html = Html_Msg<Msg>;
      using init_fn = std::function<std::tuple<Model, tea::IsQuit<Msg>, Cmd>()>;
      using view_fn = std::function<Html(Model)>;
      using update_fn = std::function<std::pair<Model, Cmd>(Model, Msg)>;
      App(init_fn init, view_fn view, update_fn update)
          : m_init(init), m_view(view), m_update(update) {};
      int run(int argc, char *argv[]) {
        // See https://github.com/gabime/spdlog
        auto logger = spdlog::rotating_logger_mt(
            "rotating_logger", "logs/rotating_log.txt", 5 * 1024 * 1024, 3);
        spdlog::set_default_logger(logger);
        spdlog::info("tea::App::run - BEGIN");

        int ch = ' '; // Variable to store the user's input

        std::queue<Msg> msg_q{};
        std::queue<Cmd> cmd_q{};
        auto [model, is_quit_msg, cmd] = m_init();
        cmd_q.push(cmd);
        // Main loop
        int loop_count{};
        while (true) {
          spdlog::default_logger()->flush();

          spdlog::info(
              "tea::App::run loop_count: {}, cmd_q size: {}, msg_q size: {}",
              loop_count, cmd_q.size(), msg_q.size());

          // render the ux
          auto ui = m_view(model);
          render(ui.doc);

          if (not cmd_q.empty()) {
            // Execute a command
            auto cmd = cmd_q.front();
            cmd_q.pop();
            if (auto msg = cmd()) {
              msg_q.push(*msg);
            }
          } else if (not msg_q.empty()) {
            auto msg = msg_q.front();
            msg_q.pop();

            // Try client provided predicate to identify QUIT msg
            if (is_quit_msg(msg)) {
              break;
            }

            // Run the message though the client
            auto const &[m, cmd] = m_update(model, msg);
            model = m;
            cmd_q.push(cmd);
          } else {
            // Wait for user input
            std::cout << ">";
            std::string dummy;
            std::getline(std::cin, dummy);
            spdlog::info("tea::App::run <Enter> + ignore dummy input");
            if (ui.event_handlers.contains("OnKey")) {
              Event key_event{{"Key", std::to_string(ch)}};
              if (auto optional_msg = ui.event_handlers["OnKey"](key_event))
                msg_q.push(*optional_msg);
            } else {
              throw std::runtime_error(std::format(
                  "DESIGN INSUFFICIENCY, tea::App::run failed to find a "
                  "binding 'OnKey' from client 'view' function"));
            }
          }
          ++loop_count;
        }
        spdlog::info("tea::App::run - END");

        return (ch == '-') ? 1 : 0;
      }

    private:
      init_fn m_init;
      view_fn m_view;
      update_fn m_update;
    };
    } // namespace tea
