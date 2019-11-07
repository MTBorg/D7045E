#--------------------------------------------------------------------------
# lab1 project
#--------------------------------------------------------------------------

FILE(GLOB lab1_headers code/*.h)
FILE(GLOB lab1_sources code/*.cc)

SET(files_example ${lab1_headers} ${lab1_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(lab1 ${files_example})
SET_TARGET_PROPERTIES(
	lab1
	PROPERTIES
		OUTPUT_NAME "lab1"
		SUFFIX ".out"
)
TARGET_LINK_LIBRARIES(lab1 core render)
ADD_DEPENDENCIES(lab1 core render)
