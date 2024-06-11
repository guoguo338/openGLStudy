cmake_minimum_required(VERSION 3.7)
project(Clion-OpenGL) # Your Project Name

add_definitions(-DDEBUG)

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glad/include)
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-arm64)

add_subdirectory(wrapper)

set(SOURCE_FILES OpenGL/src/Application.cpp Dependencies/glad/src/glad.c)
add_executable(Clion-OpenGL ${SOURCE_FILES})

target_link_libraries(Clion-OpenGL glfw3 wrapper)