cmake_minimum_required(VERSION 3.20)
project(cadance CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenCASCADE REQUIRED)
find_package(imgui REQUIRED)
find_package(GTest REQUIRED)
find_package(immer REQUIRED)
find_package(pugixml REQUIRED)
find_package(spdlog REQUIRED)

find_package(Coin3D REQUIRED)
message(STATUS "COIN3D_FOUND: ${COIN3D_FOUND}")
message(STATUS "COIN3D_INCLUDE_DIRS: ${COIN3D_INCLUDE_DIRS}")
message(STATUS "COIN3D_LIBRARIES: ${COIN3D_LIBRARIES}")

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(cadance ${SOURCES} ${HEADERS})

target_link_libraries(cadance opencascade::opencascade)
target_link_libraries(cadance imgui::imgui)
target_link_libraries(cadance gtest::gtest)
target_link_libraries(cadance immer::immer)
target_link_libraries(cadance pugixml::pugixml)
target_link_libraries(cadance spdlog::spdlog)

target_include_directories(cadance PRIVATE ${COIN3D_INCLUDE_DIRS})
target_link_libraries(cadance ${COIN3D_LIBRARIES})


install(TARGETS cadance DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
