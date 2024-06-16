cmake_minimum_required(VERSION 3.22)
project(Physics2D LANGUAGES C)

set(CMAKE_C_COMPILER /usr/bin/gcc)

file(GLOB_RECURSE SOURCE_FILES "*.c" "*.h")

add_library(${PROJECT_NAME} ${SOURCE_FILES})
add_subdirectory(Math)
add_subdirectory(DataStructs)

target_include_directories(${PROJECT_NAME} PRIVATE 
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/DataStructs
	${CMAKE_SOURCE_DIR}/Math
)
target_link_libraries(${PROJECT_NAME} PRIATE ds_module m2d_module)
