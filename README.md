# minetoss

Minecraft like engine openGL / GLFW
-----------------------------------------------

• Currently working on the rendering system: (https://github.com/toss-dev/minetoss/blob/master/includes/const.h)

A terrain is a (TERRAIN_SIZEX x TERRAIN_SIZEY x TERRAIN_SIZEZ) array size, and a 3D index in the world

Every terrain are saved in an hashmap

MESH_PER_TERRAIN meshes are built for each terrain.
Each meshes has a vbo which is filled with every visible face from a subdivision of the terrain's block array
(TERRAIN_SIZEX x (TERRAIN_SIZEY / MESH_PER_TERRAIN) x TERRAIN_SIZEZ) blocks in a mesh

Only faces in camera frustum, and close enough (CHUNK_RENDER_DISTANCE Terrains distance) are rendered (see const.h)


TODO:
	
	- reduce main thread tasks (use for rendering)
	- improve memory managment in terrani generation / deletion


--------------------------------------
Extern library used:
* OpenGL (modern pipeline)
* GLFW (opengl framework)
* glew (windows only)
* ptherad (for thread handling)
* lodepng.c lodepng.h (png decoder / encoder)
