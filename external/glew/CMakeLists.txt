project(GLEW)

cmake_minimum_required(VERSION 2.8.7)

add_library(glew STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c)
target_include_directories(glew PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(UNIX)
        target_link_libraries(glew -ldl)
endif(UNIX)
set_target_properties(glew PROPERTIES
        OUTPUT_NAME "glew"
        FOLDER "GLEW")