cmake_minimum_required (VERSION 2.8)

#extract the current directory name and replace the whitespaces by underscores: 
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

#----------------------------
#project name:
project(${ProjectId})

set(CMAKE_CXX_FLAGS "-g -Wall")
#set(CMAKE_CXX_FLAGS "-g -Wall -lGLEW  -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread")
#find_package(GLUT)
#find_package(GLM REQUIRED)
#find_package(OpenGL)

#add_definitions(-DDEF_RET_1)
#version:
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)
set (VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#OpenGL settings:
#----------------------------
include(ExternalProject)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include( Findglfw )
include( Findglm )

#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#    include_directories(${GLEW_INCLUDE_DIRS})
#    link_libraries(${GLEW_LIBRARIES})
#endif()

link_directories(${CMAKE_SOURCE_DIR}/external/) #is this line inherited by the subprojects?
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glad" "external/glad")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glew" "external/glew")
#----------------------------

include_directories(${CMAKE_SOURCE_DIR}/include) #is this line inherited by the subprojects?
#include_directories(${CMAKE_SOURCE_DIR}/external/)
#include_directories(/usr/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/soil)

#include_directories(${CMAKE_SOURCE_DIR}/external/glew/include/GL)
#link_directories(${CMAKE_SOURCE_DIR}/external/lib)

message("Binary Tree path: ${PROJECT_BINARY_DIR}")

#add subdirectories:
#add_subdirectory(include)
add_subdirectory(src)
#add_subdirectory(obj)

add_custom_target(run
    COMMAND ${CMAKE_PROJECT_NAME}
    DEPENDS ${CMAKE_PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
