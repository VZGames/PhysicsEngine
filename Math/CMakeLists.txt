file(GLOB_RECURSE SOURCE_FILES "*.c" "*.h")
add_library(m2d_module  ${SOURCE_FILES})
target_include_directories(m2d_module PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

