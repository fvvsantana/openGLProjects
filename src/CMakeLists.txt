
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
add_library(OBJECTS OBJECT ${${ProjectId}_sources})
#----------------------------

#link objects and generate a library:
#add_library(${ProjectId}lib STATIC $<TARGET_OBJECTS:OBJECTS>)
#set_target_properties( ${ProjectId}lib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OBJECTS_DIR})
#----------------------------

#move all the objects to the OBJECTS_DIR
#list of objects:
FILE(GLOB OBJECT_PATHS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/OBJECTS.dir/*.o")
install(FILES ${OBJECT_PATHS} DESTINATION ${OBJECTS_DIR})
#foreach(loop_var RANGE 9)
#    message( "${OBJECT_PATHS}" )
#    message( "batata" )
#endforeach(loop_var)
#foreach(OBJ ${OBJECT_PATHS})
#    message( "${OBJ}" )
#endforeach(OBJ)


#build executable:
#add_executable( ${EXECUTABLE} ${${ProjectId}_sources})
add_executable( ${EXECUTABLE} $<TARGET_OBJECTS:OBJECTS>)
set_target_properties( ${EXECUTABLE} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/build/src/CMakeFiles/OBJECTS.dir
#        DESTINATION ${CMAKE_SOURCE_DIR}/obj
#        FILES_MATCHING PATTERN "*.o")
#install(TARGETS ${$<TARGET_OBJECTS:OBJECTS>}
        #DESTINATION ${CMAKE_SOURCE_DIR})

