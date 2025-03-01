#include "tests.hpp"
#include <gtest/gtest.h>
// Open Cascade access
#include <BRepPrimAPI_MakeBox.hxx>

namespace test {

    namespace occt {
        // Tests related to open cascade technology c++ library
        TEST(OCCTTest, OpenCascadeAccess) {
            // Create a box with dimensions 10x10x10
            BRepPrimAPI_MakeBox box(10.0, 10.0, 10.0);
                        
            // Check if the shape is created (should not be null)
            EXPECT_TRUE(not box.Shape().IsNull());  // The shape should be valid and not null
        }
    }

    int run_all() {
        ::testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }
}