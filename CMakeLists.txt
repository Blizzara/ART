Project(ART)
Cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "-Wall -g")

# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=athlon64")

Find_Package ( SDL REQUIRED )
INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR}) 
Include_directories("/usr/local/include")	# required by pngwriter
Include_directories("/usr/include/freetype2")	# required by pngwriter
Link_directories("/usr/local/lib")		# required by pngwrite

Include_directories ("${PROJECT_SOURCE_DIR}/src")
Add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main ART)
