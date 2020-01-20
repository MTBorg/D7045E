FILE(GLOB lab4_headers code/include/*.h)
FILE(GLOB lab4_sources code/*.cpp)
INCLUDE_DIRECTORIES(code/include)

SET(files_lab4 ${lab4_headers} ${lab4_sources})
SOURCE_GROUP("lab4" FILES ${files_lab4})

ADD_EXECUTABLE(lab4-test ${files_lab4})
SET_TARGET_PROPERTIES(
	lab4-test
	PROPERTIES
		OUTPUT_NAME "lab4"
		SUFFIX ".out"
)
TARGET_LINK_LIBRARIES(lab4-test core render)
ADD_DEPENDENCIES(lab4-test core render)
