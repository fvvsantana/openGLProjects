#set variable
set(FIND_GLM_PATHS ${CMAKE_SOURCE_DIR}/external/glm)


#include the headers
#find_path(GLM_INCLUDE_DIR include/
        #PATHS ${FIND_GLM_PATHS})
#find_path(GLM_INCLUDE_DIR glm
        #PATH_SUFFIXES include
        #PATHS ${FIND_GLM_PATHS})

set(GLM_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glm/include)


#include the static library
find_library(GLM_LIBRARY
        NAMES glm
        PATH_SUFFIXES lib
        PATHS ${FIND_GLM_PATHS})
