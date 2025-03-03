cmake_minimum_required(VERSION 3.20)
project(cadance CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCASCADE REQUIRED)
find_package(imgui REQUIRED)
find_package(GTest REQUIRED)
find_package(immer REQUIRED)
find_package(pugixml)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(cadance ${SOURCES} ${HEADERS})

target_link_libraries(cadance opencascade::opencascade)
target_link_libraries(cadance imgui::imgui)
target_link_libraries(cadance gtest::gtest)
target_link_libraries(cadance immer::immer)
target_link_libraries(cadance pugixml::pugixml)

install(TARGETS cadance DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
