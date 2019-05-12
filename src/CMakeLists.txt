
#extract the current directory name and replace the whitespaces by underscores: 
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})

#----------------------------
#project name:
project(${ProjectId})
#sources files:
FILE(GLOB ${ProjectId}_sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#executable output name:
set(EXECUTABLE  ${CMAKE_PROJECT_NAME})
#objects output directory:
set(OBJECTS_DIR ${CMAKE_SOURCE_DIR}/obj)
#----------------------------

#build objects:
#----------------------------

#link objects and generate a library:
add_library(${ProjectId}lib STATIC ${${ProjectId}_sources})




#----------------------------

#OpenGL settings:
#----------------------------
#find_library(LIBGLEW GLEW ${CMAKE_SOURCE_DIR}/external)
find_library(LIBSOIL SOIL ${CMAKE_SOURCE_DIR}/external/soil)
#find_library(LIBGLM glm_static ${CMAKE_SOURCE_DIR}/external/)
#target_link_libraries(${ProjectId}lib PUBLIC ${GLFW_LIBRARIES} glad glew)
target_link_libraries(${ProjectId}lib PUBLIC ${GLFW_LIBRARIES} glad)
target_include_directories(${ProjectId}lib PUBLIC ${GLFW_INCLUDE_DIR})
#----------------------------

#move lib to objects' folder
set_target_properties( ${ProjectId}lib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OBJECTS_DIR})

#move all the objects to the OBJECTS_DIR
#list of objects:
#FILE(GLOB OBJECT_PATHS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/OBJECTS.dir/*.o")
#install(FILES ${OBJECT_PATHS} DESTINATION ${OBJECTS_DIR})
#foreach(loop_var RANGE 9)
#    message( "${OBJECT_PATHS}" )
#    message( "batata" )
#endforeach(loop_var)
#foreach(OBJ ${OBJECT_PATHS})
#    message( "${OBJ}" )
#endforeach(OBJ)


#build executable:
#add_executable( ${EXECUTABLE} ${${ProjectId}_sources})
#add_executable( ${EXECUTABLE} $<TARGET_OBJECTS:OBJECTS>)
add_executable( ${EXECUTABLE} ${${ProjectId}_sources})
#target_link_libraries(${EXECUTABLE} ${CMAKE_SOURCE_DIR}/external/glew-2.2.0/lib/libGLEW.a)
#target_link_libraries(${EXECUTABLE} ${CMAKE_SOURCE_DIR}/external/libSOIL.a)
#include(FindPkgConfig) # I think it's not necessary

#glm linking
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE} ${GLM_LIBRARY})

#glfw linking
find_package(glfw REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE} ${GLFW_LIBRARY})

#assimp linking
find_package(assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE} ${ASSIMP_LIBRARY})



target_link_libraries(${EXECUTABLE} ${ProjectId}lib)
target_link_libraries(${EXECUTABLE} ${LIBSOIL})

set_target_properties( ${EXECUTABLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/build/src/CMakeFiles/OBJECTS.dir
#        DESTINATION ${CMAKE_SOURCE_DIR}/obj
#        FILES_MATCHING PATTERN "*.o")
#install(TARGETS ${$<TARGET_OBJECTS:OBJECTS>}
        #DESTINATION ${CMAKE_SOURCE_DIR})

