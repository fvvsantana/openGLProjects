include(ExternalProject)
find_package(GLFW 3.2 QUIET)

if(GLFW_FOUND)
    message(STATUS "Found GLFW")
else()
    message(STATUS "GLFW not found - will build from source")

    ExternalProject_Add(
    glfw PREFIX glfw
    URL "https://github.com/glfw/glfw/archive/3.2.1.tar.gz"
    # URL_HASH SHA1=fe17a0610a239311a726ecabcd2dbd669fb24ca8
    CMAKE_ARGS
            "-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"
            "-DCMAKE_BUILD_TYPE=Release"
            "-DGLFW_BUILD_EXAMPLES=OFF"
            "-DGLFW_BUILD_TESTS=OFF"
            "-DGLFW_BUILD_DOCS=OFF"
    CMAKE_CACHE_ARGS
        "-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}"
        "-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}"
    )

    ExternalProject_Get_Property(glfw INSTALL_DIR)
    set(GLFW_INCLUDE_DIR ${INSTALL_DIR}/include)
    set(GLFW_LIBRARIES
        ${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3${CMAKE_STATIC_LIBRARY_SUFFIX})

    if(UNIX)
        find_package(Threads REQUIRED)
        find_package(X11 REQUIRED)

        if(NOT X11_Xrandr_FOUND)
            message(FATAL_ERROR "Xrandr library not found - required for GLFW")
        endif()

        if(NOT X11_xf86vmode_FOUND)
            message(FATAL_ERROR "xf86vmode library not found - required for GLFW")
        endif()

        if(NOT X11_Xcursor_FOUND)
            message(FATAL_ERROR "Xcursor library not found - required for GLFW")
        endif()

        if(NOT X11_Xinerama_FOUND)
            message(FATAL_ERROR "Xinerama library not found - required for GLFW")
        endif()

        if(NOT X11_Xinput_FOUND)
            message(FATAL_ERROR "Xinput library not found - required for GLFW")
        endif()

        if(APPLE)
           list(APPEND GLFW_LIBRARIES
            "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}"
            "${X11_Xinerama_LIB}" "${X11_Xinput_LIB}"
            "${CMAKE_THREAD_LIBS_INIT}" -ldl)

            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit")
            find_library(COCOA_LIBRARY Cocoa)
            find_library(CV_LIBRARY CoreVideo)
            list(APPEND GLFW_LIBRARIES ${GLFW_LIBRARIES} ${COCOA_LIBRARY} ${CV_LIBRARY})

        else(APPLE)
          list(APPEND GLFW_LIBRARIES
            -lX11
            "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}"
            "${X11_Xinerama_LIB}" "${X11_Xinput_LIB}"
            "${CMAKE_THREAD_LIBS_INIT}" -ldl -lm)


        endif(APPLE)
    endif()
endif()

set(GLFW_INCLUDE_DIR ${GLFW_INCLUDE_DIR} CACHE STRING "")
set(GLFW_LIBRARIES ${GLFW_LIBRARIES} CACHE STRING "")