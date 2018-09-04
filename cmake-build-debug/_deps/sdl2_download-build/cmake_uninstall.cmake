if (NOT EXISTS "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/install_manifest.txt\"")
endif(NOT EXISTS "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/install_manifest.txt")

file(READ "/goinfre/lvan-gen/Documents/OpenGLLearning/cmake-build-debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND /goinfre/lvan-gen/.brew/Cellar/cmake/3.11.4/bin/cmake -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

