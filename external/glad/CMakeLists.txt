project(GLAD)

cmake_minimum_required(VERSION 2.8.7)

add_library(glad STATIC glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(UNIX)
        target_link_libraries(glad -ldl)
endif(UNIX)
set_target_properties(glad PROPERTIES
        OUTPUT_NAME "glad"
        FOLDER "GLAD")