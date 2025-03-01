cmake_minimum_required(VERSION 3.15)
project(cadance CXX)

find_package(OpenCASCADE REQUIRED)
find_package(GTest REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(cadance ${SOURCES} ${HEADERS})

target_link_libraries(cadance opencascade::opencascade)
target_link_libraries(cadance gtest::gtest)

install(TARGETS cadance DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
