# Install script for directory: /goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/goinfre/lvan-gen/.brew")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/libSDL2d.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/libSDL2d.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/libSDL2maind.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2maind.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2maind.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2maind.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources/SDL2Targets.cmake"
         "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/CMakeFiles/Export/SDL2.framework/Resources/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources" TYPE FILE FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/CMakeFiles/Export/SDL2.framework/Resources/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources" TYPE FILE FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/CMakeFiles/Export/SDL2.framework/Resources/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/SDL2.framework/Resources" TYPE FILE FILES
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/SDL2Config.cmake"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_assert.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_atomic.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_audio.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_bits.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_blendmode.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_clipboard.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_android.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_iphoneos.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_macosx.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_minimal.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_pandora.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_psp.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_windows.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_winrt.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_config_wiz.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_copying.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_cpuinfo.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_egl.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_endian.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_error.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_events.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_filesystem.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_gamecontroller.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_gesture.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_haptic.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_hints.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_joystick.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_keyboard.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_keycode.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_loadso.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_log.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_main.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_messagebox.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_mouse.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_mutex.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_name.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengl.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengl_glext.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengles.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengles2.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengles2_gl2.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengles2_gl2ext.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengles2_gl2platform.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_opengles2_khrplatform.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_pixels.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_platform.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_power.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_quit.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_rect.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_render.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_revision.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_rwops.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_scancode.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_shape.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_stdinc.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_surface.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_system.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_syswm.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_assert.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_common.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_compare.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_crc32.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_font.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_fuzzer.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_harness.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_images.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_log.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_md5.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_memory.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_test_random.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_thread.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_timer.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_touch.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_types.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_version.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_video.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/SDL_vulkan.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/begin_code.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/include/close_code.h"
    "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/include/SDL_config.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  
          execute_process(COMMAND /goinfre/lvan-gen/.brew/Cellar/cmake/3.11.4/bin/cmake -E create_symlink
          "libSDL2-2.0.dylib" "libSDL2.dylib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/libSDL2.dylib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/sdl2.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-build/sdl2-config")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/goinfre/lvan-gen/.brew/share/aclocal/sdl2.m4")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/goinfre/lvan-gen/.brew/share/aclocal" TYPE FILE FILES "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/_deps/sdl2_download-src/sdl2.m4")
endif()

