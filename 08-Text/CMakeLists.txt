cmake_minimum_required(VERSION 3.1)

project(08-Text)

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

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2 COMPONENTS graphics REQUIRED)
add_executable(08-Text src/main.cpp src/Sokoban.cpp src/Map.cpp src/Box.cpp)
target_link_libraries(08-Text sfml-graphics sfml-audio)