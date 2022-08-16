cmake_minimum_required(VERSION 3.16)

project(cppFiles LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE") # defining macro for debug mode

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # if(GNU) doesn't work here for some reason
	# Enable Address Sanitizer for GCC
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")
endif()

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

add_subdirectory(src)

add_library(
	hashlib
	lib/hash-library/sha1.cpp 
	lib/hash-library/sha1.h
)

target_include_directories(${PROJECT_NAME} PUBLIC lib/)

target_link_libraries(
	${PROJECT_NAME}
	hashlib
)

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG};/fsanitize=address;")
	target_compile_options(${PROJECT_NAME} PUBLIC "/W4;")

elseif(GNU OR Clang)
	set(GCC_CLANG_COMPILE_OPTIONS "-Wall;-Wextra;")
	set(GCC_CLANG_COMPILE_OPTIONS_DEBUG "-g;-O0")
	set(GCC_CLANG_COMPILE_OPTIONS_RELEASE "-O3")

	target_compile_options(${PROJECT_NAME} PUBLIC ${GCC_CLANG_COMPILE_OPTIONS})
	target_compile_options(${PROJECT_NAME} PUBLIC $<CONFIG:Debug>:${GCC_CLANG_COMPILE_OPTIONS_DEBUG})
	target_compile_options(${PROJECT_NAME} PUBLIC $<CONFIG:Release>:${GCC_CLANG_COMPILE_OPTIONS_RELEASE})

	if (LINUX)
		target_link_libraries(${PROJECT_NAME} PUBLIC pthreads)
	endif()
	
endif()