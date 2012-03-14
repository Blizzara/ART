set (
   SOURCES
   Box.cpp
   Camera.cpp
   CmdParser.cpp
   Intersection.cpp
   IsaacRand.cc
   Light.cpp
   Plane.cpp
   Primitive.cpp
   Ray.cpp
   RTEngine.cpp
   Scene.cpp
   SDLEngine.cpp
   Sphere.cpp
   Texture.cpp
   Timer.cpp
   Triangle.cpp
   Vector.cpp
   Write.cpp
   art.cpp
)

# REQUIRED does not work in CMake <=2.4.6 for SDL
# Find_Package ( SDL REQUIRED )
# INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR}) 
# Include_directories("/usr/local/include")	# required by pngwriter
# Include_directories("/usr/include/freetype2")	# required by pngwriter
# Link_directories("/usr/local/lib")		# required by pngwrite
#Find_Package ( SDL_image REQUIRED ) # if using SDL_image

# Workaround for the non-working REQUIRED flag
# if ( NOT SDL_FOUND )
#    message ( FATAL_ERROR "SDL not found!" )
# endif ( NOT SDL_FOUND )

# include(FindSDL)

link_libraries (
   ${SDL_LIBRARY}
   			# these are
   pngwriter		# required
   png   		# pngwriter 
   z			# by
)

add_library (
   ART
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)
