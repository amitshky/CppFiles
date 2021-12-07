cmake_minimum_required(VERSION 3.16)

project(cppFiles LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # if(GNU) doesn't work here for some reason
	# Enable Address Sanitizer for GCC
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()


if(NOT CMAKE_BUILD_TYPE) # build type defaulted to release of not specified
	set(CMAKE_BUILD_TYPE Release)
endif()

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

add_subdirectory(src)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC "/W3;")

elseif(GNU)
	set(GCC_COMPILE_OPTIONS "-Wall;-Wextra;")
	set(GCC_COMPILE_OPTIONS_DEBUG "-g")
	set(GCC_COMPILE_OPTIONS_RELEASE "-O3")

	target_compile_options(${PROJECT_NAME} PUBLIC ${GCC_COMPILE_OPTIONS})
	target_compile_options(${PROJECT_NAME} PUBLIC $<CONFIG:Debug>:${GCC_COMPILE_OPTIONS_DEBUG})
	target_compile_options(${PROJECT_NAME} PUBLIC $<CONFIG:Release>:${GCC_COMPILE_OPTIONS_RELEASE})

	if (LINUX)
		target_link_libraries(${PROJECT_NAME} PUBLIC pthreads)
	endif()
	
endif()