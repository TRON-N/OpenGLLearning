cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
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
    set(glad_SOURCE_FILE "${glad_download_SOURCE_DIR}/src/glad.c")
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
    set(ENABLE_BOOST_WORKAROUND ON CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_ASSIMP_SAMPLES OFF CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    FetchContent_Populate(assimp_download)
    add_subdirectory(${assimp_download_SOURCE_DIR} ${assimp_download_BINARY_DIR})
    include_directories("${assimp_download_SOURCE_DIR}/include")
    include_directories("${assimp_download_BINARY_DIR}/include")
endif()

FetchContent_Declare(
        extern_download
        GIT_REPOSITORY https://github.com/TRON-N/externalRescourcesForOpenGLLearning.git
)

FetchContent_GetProperties(extern_download)

if(NOT extern_download_POPULATED)
    FetchContent_Populate(extern_download)
    add_subdirectory(${extern_download_SOURCE_DIR} ${extern_download_BINARY_DIR})
    include_directories("${extern_download_SOURCE_DIR}")
    include_directories("${extern_download_SOURCE_DIR}/stb_image")
endif()

add_executable(learningOpenGL main.cpp ${glad_SOURCE_FILE} OpenGLClasses/VertexBuffer.cpp OpenGLClasses/VertexBuffer.hpp OpenGLClasses/VertexArray.cpp OpenGLClasses/VertexArray.cpp OpenGLClasses/VertexArray.hpp OpenGLClasses/ElementBuffer.cpp OpenGLClasses/ElementBuffer.hpp OpenGLClasses/Shader.cpp OpenGLClasses/Shader.hpp OpenGLClasses/openGLFunctionCallErrorManagementWrapper.hpp OpenGLClasses/openGLErrorManagementFunctions.cpp OpenGLClasses/BufferLayout/VertexBufferLayout.cpp OpenGLClasses/BufferLayout/VertexBufferLayout.hpp OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterpreter.cpp OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterpreter.hpp OpenGLClasses/ModelManagement/s_VertexData.hpp OpenGLClasses/ModelManagement/Texture.cpp OpenGLClasses/ModelManagement/Texture.hpp OpenGLClasses/ModelManagement/Models/Model.cpp OpenGLClasses/ModelManagement/Models/Model.hpp OpenGLClasses/ModelManagement/Models/Transformation.cpp OpenGLClasses/ModelManagement/Models/Transformation.hpp OpenGLClasses/ModelManagement/Animation/KeyFrame.cpp OpenGLClasses/ModelManagement/Animation/KeyFrame.hpp OpenGLClasses/ModelManagement/Animation/Animation.cpp OpenGLClasses/ModelManagement/Animation/Animation.hpp OpenGLClasses/BufferLayout/LayoutElement.cpp OpenGLClasses/BufferLayout/LayoutElement.hpp OpenGLClasses/ModelManagement/Models/ModelMesh.cpp OpenGLClasses/ModelManagement/Models/ModelMesh.hpp OpenGLClasses/ObserverPattern/i_Observer.hpp OpenGLClasses/ObserverPattern/Observable.cpp OpenGLClasses/ObserverPattern/Observable.hpp OpenGLClasses/Camera.cpp OpenGLClasses/Camera.hpp)
target_link_libraries(learningOpenGL SDL2main SDL2-static assimp stb_image_lib)
#target_compile_options(learningOpenGL PRIVATE "-Wall" "-Werror" "-Wextra")