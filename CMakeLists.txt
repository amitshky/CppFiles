cmake_minimum_required(VERSION 3.16)

project(cppFiles)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE) # build type defaulted to release of not specified
	set(CMAKE_BUILD_TYPE Release)
endif()

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

add_subdirectory(src)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC "/W3")

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