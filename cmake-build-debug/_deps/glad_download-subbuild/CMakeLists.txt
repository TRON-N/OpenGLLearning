# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.11.4)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(glad_download-populate NONE)

include(ExternalProject)
ExternalProject_Add(glad_download-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/TRON-N/gladForNibbler.git"
                    SOURCE_DIR          "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/glad_download-src"
                    BINARY_DIR          "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/glad_download-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
)
