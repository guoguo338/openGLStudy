cmake_minimum_required(VERSION 3.7)
project(Clion-OpenGL) # Your Project Name

add_definitions(-DDEBUG)

set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -std=c++11")

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glad/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/)
include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib-arm64)

add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glFramework)

set(SOURCE_FILES OpenGL/src/main.cpp Dependencies/glad/src/glad.c)
add_executable(Clion-OpenGL ${SOURCE_FILES})

target_link_libraries(Clion-OpenGL glfw3 wrapper app fw)