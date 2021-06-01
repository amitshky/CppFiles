cmake_minimum_required(VERSION 3.16)

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

project(cppFiles)

add_subdirectory(src)

if (LINUX)
	target_link_libraries("${PROJECT_NAME}" PUBLIC pthread)
endif()