# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.11.4)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(sdl2_download-populate NONE)

include(ExternalProject)
ExternalProject_Add(sdl2_download-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://www.libsdl.org/release/SDL2-2.0.8.zip"
                    SOURCE_DIR          "C:/Users/User/Documents/WTC/openGL/learningOpenGL/cmake-build-debug/_deps/sdl2_download-src"
                    BINARY_DIR          "C:/Users/User/Documents/WTC/openGL/learningOpenGL/cmake-build-debug/_deps/sdl2_download-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
