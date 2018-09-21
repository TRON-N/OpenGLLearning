cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(OpenglGraphicsLib)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        glad_download
        GIT_REPOSITORY https://github.com/TRON-N/gladForNibbler.git
)

FetchContent_GetProperties(glad_download)

if (NOT glad_download_POPULATED)
    FetchContent_Populate(glad_download)
    set(glad_SOURCE_FILE "${glad_download_SOURCE_DIR}/src/glad.c")
endif ()

FetchContent_Declare(
        assimp_download
        URL https://github.com/assimp/assimp/archive/v4.1.0.zip
)

FetchContent_GetProperties(assimp_download)

if (NOT assimp_download_POPULATED)
    set(ENABLE_BOOST_WORKAROUND ON CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_ASSIMP_SAMPLES OFF CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    FetchContent_Populate(assimp_download)
    add_subdirectory(${assimp_download_SOURCE_DIR} ${assimp_download_BINARY_DIR})
endif ()

FetchContent_Declare(
        stb_image_download
        GIT_REPOSITORY https://github.com/TRON-N/externalRescourcesForOpenGLLearning.git
)

FetchContent_GetProperties(stb_image_download)

if (NOT stb_image_download_POPULATED)
    FetchContent_Populate(stb_image_download)
    add_subdirectory(${stb_image_download_SOURCE_DIR} ${stb_image_download_BINARY_DIR})
endif ()

set(CPP_SOURCE_FILES OpenGLClasses/ObserverPattern/Observable.cpp
        OpenGLClasses/BufferLayout/LayoutElement.hpp
        OpenGLClasses/ModelManagement/Models/ModelMesh.cpp
        OpenGLClasses/ModelManagement/Models/Model.cpp
        OpenGLClasses/ModelManagement/Texture.cpp
        OpenGLClasses/openGLErrorManagementFunctions.cpp
        OpenGLClasses/BufferLayout/VertexBufferLayout.cpp
        OpenGLClasses/BufferLayout/VertexBufferLayout.hpp
        OpenGLClasses/ModelManagement/AssimpInterperater/AssimpInterpreter.cpp
        OpenGLClasses/Shader.cpp
        OpenGLClasses/ElementBuffer.cpp
        OpenGLClasses/VertexArray.cpp
        OpenGLClasses/VertexArray.cpp
        OpenGLClasses/VertexBuffer.cpp
        ExceptionClass/GenericProgException.cpp
        ${glad_SOURCE_FILE})

set(HEADER_FILES Includes/VertexBuffer.hpp
        Includes/VertexArray.hpp
        Includes/ElementBuffer.hpp
        Includes/openGLFunctionCallErrorManagementWrapper.hpp
        Includes/Shader.hpp
        Includes/AssimpInterpreter.hpp
        Includes/s_VertexData.hpp
        Includes/Texture.hpp
        Includes/Model.hpp OpenGLClasses/ModelManagement/Models/Transformation.cpp
        Includes/Transformation.hpp OpenGLClasses/ModelManagement/Animation/KeyFrame.cpp
        Includes/KeyFrame.hpp OpenGLClasses/ModelManagement/Animation/Animation.cpp
        Includes/Animation.hpp OpenGLClasses/BufferLayout/LayoutElement.cpp
        Includes/ModelMesh.hpp Includes/i_Observer.hpp
        Includes/Observable.hpp OpenGLClasses/Camera.cpp
        Includes/Camera.hpp OpenGLClasses/Renderer.cpp
        Includes/Renderer.hpp OpenGLClasses/Window.cpp
        Includes/Window.hpp OpenGLClasses/ModelManagement/Models/ModelDispenser.cpp
        Includes/ModelDispenser.hpp
        Includes/GenericProgException.hpp)

add_library(OpenglGraphicsLib STATIC ${CPP_SOURCE_FILES} ${HEADER_FILES})
target_include_directories(OpenglGraphicsLib PRIVATE Includes)

if (stb_image_download_POPULATED)
    target_include_directories(OpenglGraphicsLib PUBLIC "${stb_image_download_SOURCE_DIR}/stb_image")
endif ()

if (glad_download_POPULATED)
    target_include_directories(OpenglGraphicsLib PUBLIC ${glad_download_SOURCE_DIR}/include)
endif ()

if (assimp_download_POPULATED)
    target_include_directories(OpenglGraphicsLib PUBLIC ${assimp_download_SOURCE_DIR}/include)
    target_include_directories(OpenglGraphicsLib PUBLIC ${assimp_download_BINARY_DIR}/include)
endif ()

target_link_libraries(OpenglGraphicsLib assimp stb_image_lib)
#target_compile_options(OpenglGraphicsLib PRIVATE "-Wall" "-Werror" "-Wextra")