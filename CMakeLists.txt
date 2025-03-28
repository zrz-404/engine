cmake_minimum_required(VERSION 3.16)
project(MyGameEngine VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_TESTS "Build tests" OFF)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/external
)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Add GLAD
add_library(glad STATIC
    ${PROJECT_SOURCE_DIR}/external/glad/src/glad.c
)
target_include_directories(glad PUBLIC
    ${PROJECT_SOURCE_DIR}/external/glad/include
)

# Gather source files
file(GLOB_RECURSE ENGINE_SOURCES 
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Engine library
add_library(engine STATIC
    ${ENGINE_SOURCES}
)

target_link_libraries(engine PUBLIC
    OpenGL::GL
    glfw
    glad
)

# Main executable
add_executable(engine_app 
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(engine_app PRIVATE
    engine
)

# Copy assets to build directory
add_custom_command(TARGET engine_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:engine_app>/assets
)

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install
install(TARGETS engine_app
    RUNTIME DESTINATION bin
)
