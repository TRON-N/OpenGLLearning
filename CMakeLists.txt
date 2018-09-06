cmake_minimum_required(VERSION 3.11)
project(learningOpenGL)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        glad_download
        GIT_REPOSITORY https://github.com/TRON-N/gladForNibbler.git
)

FetchContent_GetProperties(glad_download)

if(NOT glad_download_POPULATED)
    FetchContent_Populate(glad_download)
    include_directories(${glad_download_SOURCE_DIR}/include)
    set(glad_SOURCE_FILE "${glad_download_SOURCE_DIR}/src/glad.c" OpenGLClasses/BufferLayout/LayoutElement.cpp OpenGLClasses/BufferLayout/LayoutElement.hpp OpenGLClasses/Models/Model.cpp OpenGLClasses/Models/Model.hpp)
endif()

FetchContent_Declare(
        sdl2_download
        URL https://www.libsdl.org/release/SDL2-2.0.8.zip
)

FetchContent_GetProperties(sdl2_download)

if(NOT sdl2_download_POPULATED)
    FetchContent_Populate(sdl2_download)
    add_subdirectory(${sdl2_download_SOURCE_DIR} ${sdl2_download_BINARY_DIR})
    include_directories("${sdl2_download_SOURCE_DIR}/include")
endif()

FetchContent_Declare(
        assimp_download
        URL https://github.com/assimp/assimp/archive/v4.1.0.zip
)

FetchContent_GetProperties(assimp_download)

if(NOT assimp_download_POPULATED)
#    set(ENABLE_BOOST_WORKAROUND OFF CACHE BOOL "" FORCE)
    FetchContent_Populate(assimp_download)
    add_subdirectory(${assimp_download_SOURCE_DIR} ${assimp_download_BINARY_DIR})
    include_directories("${assimp_download_SOURCE_DIR}/include")
    include_directories("${assimp_download_BINARY_DIR}/include")
endif()

include_directories(extern/glm-stable/)


add_executable(learningOpenGL main.cpp ${glad_SOURCE_FILE} extern/stb_image.h OpenGLClasses/VertexBuffer.cpp OpenGLClasses/VertexBuffer.hpp OpenGLClasses/VertexArray.cpp OpenGLClasses/VertexArray.cpp OpenGLClasses/VertexArray.hpp OpenGLClasses/ElementBuffer.cpp OpenGLClasses/ElementBuffer.hpp  OpenGLClasses/Shader.cpp OpenGLClasses/Shader.hpp OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp OpenGLClasses/openGLErrorManagementFunctions.cpp extern/stb_file.cpp OpenGLClasses/BufferLayout/VertexBufferLayout.cpp OpenGLClasses/BufferLayout/VertexBufferLayout.hpp OpenGLClasses/AssimpInterperater/AssimpInterperater.cpp OpenGLClasses/AssimpInterperater/AssimpInterperater.hpp)
target_link_libraries(learningOpenGL SDL2main SDL2-static assimp)