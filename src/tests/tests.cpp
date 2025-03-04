#include "tests.hpp"
#include <memory> // E.g., unique_ptr
#include <gtest/gtest.h>

// GLFW access
#include <GLFW/glfw3.h>
// Open Cascade access
#include <BRepPrimAPI_MakeBox.hxx>
// ImGui access
#include "imgui.h"
// Immer access
#include <immer/vector.hpp>
// PugiXML access
#include <pugixml.hpp>
// spdlog access
#include <spdlog/spdlog.h> 
#include <spdlog/sinks/rotating_file_sink.h>
// Coin3D access
#include <Inventor/SoDB.h>
#include <Inventor/nodes/SoSeparator.h>


namespace test {

    namespace glfw_suite {
        // Tests related to dependance on glfw 
        struct GLFW_RAII {
            bool m_init_ok{};
            GLFW_RAII() {
                m_init_ok = glfwInit();
            }
            ~GLFW_RAII() {
                if (m_init_ok) glfwTerminate();
            }
        };
        TEST(GLFWTest,GLFWAccessTest) {
            GLFW_RAII glfw_raii{};
            EXPECT_TRUE(glfw_raii.m_init_ok);
        }
    }

    namespace occt_suite {
        // Tests related to dependancies on the open cascade technology c++ library
        TEST(OCCTTest, OpenCascadeAccess) {
            BRepPrimAPI_MakeBox box(10.0, 10.0, 10.0);
            EXPECT_FALSE(box.Shape().IsNull());
        }
    } // namespace occt

    namespace imgui_suite {
        // Tests related to dependancies on the ImGui C++ library
        
        // RAII for ImGui current and new test context
        class ImGuiContextManager {
        public:
            ImGuiContextManager() 
                :  m_previousContext(ImGui::GetCurrentContext())
                  ,m_context(ImGui::CreateContext(), [](ImGuiContext* ctx) {
                        if (ctx) ImGui::DestroyContext(ctx);
                    }) 
            {}
        
            ~ImGuiContextManager() {
                // Restore the previous context when this object goes out of scope
                if (m_previousContext) {
                    ImGui::SetCurrentContext(m_previousContext);
                }
            }

            auto const& context() const {return m_context;}
        
            ImGuiContextManager(const ImGuiContextManager&) = delete;
            ImGuiContextManager& operator=(const ImGuiContextManager&) = delete;        
            ImGuiContextManager(ImGuiContextManager&&) noexcept = default;
            ImGuiContextManager& operator=(ImGuiContextManager&&) noexcept = default;
        
        private:
            ImGuiContext* m_previousContext;  // Previous context to restore later
            std::unique_ptr<ImGuiContext, void(*)(ImGuiContext*)> m_context;  // RAII-managed ImGui context
        };

        TEST(ImGuiTest, ImGuiBasicInitialization) {
            ImGuiContextManager imgui_context_raii{};
            EXPECT_TRUE(imgui_context_raii.context());
        }        
        
    } // namespace imgui

    namespace immer_suite {
        TEST(ImmerAccessTest, BasicVectorOperations) {
            // Create an immutable vector
            immer::vector<int> v1;
            
            // Add an element (returns a new vector)
            auto v2 = v1.push_back(42);
        
            // The old vector should remain empty
            EXPECT_TRUE(v1.empty());
        
            // The new vector should contain exactly one element: 42
            EXPECT_EQ(v2.size(), 1);
            EXPECT_EQ(v2[0], 42);
        }
    } // namespace immer_suite

    namespace cpp_suite {
        TEST(Cpp23FeatureTest, DetectCpp23Support) {
            bool cpp23_supported{};
            // Check if the compiler is using C++23 or later
            if constexpr (__cplusplus >= 202302L) {
                cpp23_supported = true;
            }
            EXPECT_TRUE(cpp23_supported);
        }        
    }

    namespace pugixml_suite {
        TEST(PugiXMLTest, CanParseBasicXML) {
            // Sample XML
            const char* xml = "<root><child>value</child></root>";
        
            // Load into pugixml
            pugi::xml_document doc;
            pugi::xml_parse_result result = doc.load_string(xml);
        
            // Check if parsing was successful
            ASSERT_TRUE(result) << "Failed to parse XML: " << result.description();
        
            // Verify content
            pugi::xml_node root = doc.child("root");
            ASSERT_TRUE(root) << "Root node not found";
        
            pugi::xml_node child = root.child("child");
            ASSERT_TRUE(child) << "Child node not found";
        
            EXPECT_STREQ(child.child_value(), "value");
        }        
    } // namespace pugixml_suite {

    namespace spdlog_suite {
        TEST(SpdLogTest, CanProduceLog) {
        try {
            auto logger = spdlog::rotating_logger_mt(
                "rotating_logger", "logs/rotating_log.txt", 5 * 1024 * 1024, 3);
            spdlog::set_default_logger(logger);
            spdlog::info("'TEST(SpdLogTest, CanProduceLog)' test output");
            spdlog::default_logger()->flush();
        } 
        catch (std::exception& e) {
            FAIL() << "Exception: " << std::quoted(e.what());
        }
        }
    } // namespace spdlog_suite

    namespace coin3d_suite {

        TEST(Coin3DTest, InitializeAndCreateNode) {
            // Initialize Coin3D database
            SoDB::init();
        
            // Create a simple scene graph
            SoSeparator* root = new SoSeparator;
            root->ref();  // Reference it to prevent deletion
        
            // Ensure the root node is not null
            ASSERT_NE(root, nullptr);
        
            // Clean up
            root->unref();  // Unreference it to allow deletion
        }        

    } // namespace coin3d_suite {

    int run_all() {
        ::testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }
}