cmake_minimum_required(VERSION 3.27)
project(TestWindow)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        TestWindow
        main.cpp
        vendor/glad/src/glad.c
)

# Include directories
include_directories(
        vendor/glfw/include
        vendor/glad/include
)

# Link libraries
target_link_libraries(TestWindow ${PROJECT_SOURCE_DIR}/vendor/glfw/lib/glfw3.lib)

# Library directories
link_directories(vendor/glfw/lib)