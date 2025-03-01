#include "tests.hpp"
#include <memory> // E.g., unique_ptr
#include <gtest/gtest.h>
// Open Cascade access
#include <BRepPrimAPI_MakeBox.hxx>
// ImGui access
#include "imgui.h"

namespace test {

    namespace occt {
        // Tests related to dependancies on the open cascade technology c++ library
        TEST(OCCTTest, OpenCascadeAccess) {
            BRepPrimAPI_MakeBox box(10.0, 10.0, 10.0);
            EXPECT_FALSE(box.Shape().IsNull());
        }
    }

    namespace imgui {
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
        
    }

    int run_all() {
        ::testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }
}