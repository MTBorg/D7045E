FILE(GLOB lab3_headers code/include/*.h)
FILE(GLOB lab3_sources code/*.cpp)
INCLUDE_DIRECTORIES(code/include)

SET(files_lab3 ${lab3_headers} ${lab3_sources})
SOURCE_GROUP("lab3" FILES ${files_lab3})

ADD_EXECUTABLE(lab3-test ${files_lab3})
SET_TARGET_PROPERTIES(
	lab3-test
	PROPERTIES
		OUTPUT_NAME "lab3"
		SUFFIX ".out"
)
TARGET_LINK_LIBRARIES(lab3-test core render)
ADD_DEPENDENCIES(lab3-test core render)
