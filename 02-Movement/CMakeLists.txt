cmake_minimum_required(VERSION 3.1)

project(02-Movement)

# Used for local testing
#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR "../libs/lib/cmake/SFML")
#if(WIN32 AND MSVC)
#	foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
#		if(${flag} MATCHES "/MD")
#		string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
#		endif()
#    endforeach()
#endif()

set (CMAKE_CXX_STANDARD 17)

find_package(SFML 2 COMPONENTS graphics REQUIRED)
add_executable(02-Movement src/main.cpp)
target_link_libraries(02-Movement sfml-graphics)