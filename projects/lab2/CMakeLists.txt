#--------------------------------------------------------------------------
# lab2 project
#--------------------------------------------------------------------------

FILE(GLOB lab2_headers code/*.h)
FILE(GLOB lab2_sources code/*.cpp)

SET(files_example ${lab2_headers} ${lab2_sources})
SOURCE_GROUP("lab2" FILES ${files_example})

ADD_EXECUTABLE(lab2 ${files_example})
SET_TARGET_PROPERTIES(
	lab2
	PROPERTIES
		OUTPUT_NAME "lab2"
		SUFFIX ".out"
)
TARGET_LINK_LIBRARIES(lab2 core render)
ADD_DEPENDENCIES(lab2 core render)
