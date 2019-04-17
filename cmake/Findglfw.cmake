#set variable
set(FIND_GLFW_PATHS ${CMAKE_SOURCE_DIR}/external/glfw)


#include the headers
#find_path(GLM_INCLUDE_DIR include/
        #PATHS ${FIND_GLM_PATHS})
#find_path(GLM_INCLUDE_DIR glm
        #PATH_SUFFIXES include
        #PATHS ${FIND_GLM_PATHS})

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glfw/include)


#include the static library
find_library(GLFW_LIBRARY
        NAMES glfw3
        PATH_SUFFIXES lib
        PATHS ${FIND_GLFW_PATHS})

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

    list(APPEND GLFW_LIBRARIES
        "${X11_Xrandr_LIB}" "${X11_Xxf86vm_LIB}" "${X11_Xcursor_LIB}"
        "${X11_Xinerama_LIB}" "${X11_Xinput_LIB}"
        "${CMAKE_THREAD_LIBS_INIT}" -lrt -ldl -lm -lX11)
endif()
