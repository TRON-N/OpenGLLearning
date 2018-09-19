cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(OpenglLearning)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        sdl2_download
        URL https://www.libsdl.org/release/SDL2-2.0.8.zip
)

FetchContent_GetProperties(sdl2_download)

if (NOT sdl2_download_POPULATED)
    FetchContent_Populate(sdl2_download)
    add_subdirectory(${sdl2_download_SOURCE_DIR} ${sdl2_download_BINARY_DIR})
    include_directories("${sdl2_download_SOURCE_DIR}/include")
endif ()

FetchContent_Declare(
        glm_download
        GIT_REPOSITORY https://github.com/TRON-N/glmExternalResource.git
)

FetchContent_GetProperties(glm_download)

if (NOT glm_download_POPULATED)
    FetchContent_Populate(glm_download)
    include_directories("${glm_download_SOURCE_DIR}")
endif()


include_directories(OpenglGraphicsLib/Includes)

add_subdirectory(OpenglGraphicsLib)
add_executable(openglLearning main.cpp)

target_include_directories(openglLearning PRIVATE OpenglGraphicsLib)

target_link_libraries(openglLearning SDL2-static SDL2main OpenglGraphicsLib)