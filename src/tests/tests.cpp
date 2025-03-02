#include "tests.hpp"
#include <memory> // E.g., unique_ptr
#include <gtest/gtest.h>
// Open Cascade access
#include <BRepPrimAPI_MakeBox.hxx>
// ImGui access
#include "imgui.h"
// Immer access
#include <immer/vector.hpp>

namespace test {

    namespace occt {
        // Tests related to dependancies on the open cascade technology c++ library
        TEST(OCCTTest, OpenCascadeAccess) {
            BRepPrimAPI_MakeBox box(10.0, 10.0, 10.0);
            EXPECT_FALSE(box.Shape().IsNull());
        }
    } // namespace occt

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

    namespace cpp {
        TEST(Cpp23FeatureTest, DetectCpp23Support) {
            bool cpp23_supported{};
            // Check if the compiler is using C++23 or later
            if constexpr (__cplusplus >= 202302L) {
                cpp23_supported = true;
            }
            EXPECT_TRUE(cpp23_supported);
        }        
    }

    int run_all() {
        ::testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }
}