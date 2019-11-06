#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

FILE(GLOB example_headers code/*.h)
FILE(GLOB example_sources code/*.cc)

SET(files_example ${example_headers} ${example_sources})
SOURCE_GROUP("example" FILES ${files_example})

ADD_EXECUTABLE(example ${files_example})
SET_TARGET_PROPERTIES(
	example
	PROPERTIES
		OUTPUT_NAME "example"
		SUFFIX ".out"
)
TARGET_LINK_LIBRARIES(example core render)
ADD_DEPENDENCIES(example core render)
