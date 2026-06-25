cmake_minimum_required(VERSION 3.16)

project(stacking-dream VERSION 1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_library(glad_obj OBJECT lib/glad/src/glad.c)
target_include_directories(glad_obj PRIVATE lib/glad/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

add_executable(stacking-dream)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "src/*.c"
    "src/*.h"
)

target_sources(stacking-dream PRIVATE ${SRC_FILES})

target_include_directories(stacking-dream PRIVATE
    lib/glad/include
    lib/cglm/include
    lib/glfw/include
    lib/stb
)

target_link_libraries(stacking-dream PRIVATE
    glad_obj
    glfw
    m
    ${CMAKE_DL_LIBS}
)
