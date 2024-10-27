cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(GLEW_INCLUDE_DIR "./libs/glew-2.1.0/include")
set(GLFW_INCLUDE_DIR "./libs/glfw-3.4.bin.WIN64/include")
set(GLM_INCLUDE_DIR "./libs/glm-master")

set(GLEW_LIBRARY_DIR "./libs/glew-2.1.0/lib/Release/x64")
set(GLFW_LIBRARY_DIR "./libs/glfw-3.4.bin.WIN64/lib-mingw-w64")

link_directories(${GLEW_LIBRARY_DIR})
link_directories(${GLFW_LIBRARY_DIR})

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

add_executable(MyProject main.cpp)

target_link_libraries(MyProject PRIVATE
        opengl32.lib
        glfw3.lib
        glew32.lib
        glu32.lib
)