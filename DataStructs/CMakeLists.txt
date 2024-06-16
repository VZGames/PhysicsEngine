file(GLOB_RECURSE SOURCE_FILES "*.c" "*.h")
add_library(ds_module ${SOURCE_FILES})

target_link_libraries(ds_module PRIVATE m2d_module)
target_include_directories(ds_module PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

