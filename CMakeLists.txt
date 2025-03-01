cmake_minimum_required(VERSION 3.15)
project(cadance CXX)



add_executable(cadance src/cadance.cpp src/main.cpp)



install(TARGETS cadance DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
