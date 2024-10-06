cmake_minimum_required(VERSION 3.14)
project(OpenGLApp)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME "projetOpenGL")

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8  # You can change this tag to the version you want
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v0.1.34  # You can change this tag to the version you want
)
FetchContent_MakeAvailable(glad)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${glad_SOURCE_DIR}/include)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE glfw glad)

find_package(OpenGL REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE OpenGL::GL)




