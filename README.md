# minetoss

Minecraft like engine openGL / GLFW
-----------------------------------------------

• Currently working on the rendering system: (https://github.com/toss-dev/minetoss/blob/master/includes/const.h)

terrain are (TERRAIN_SIZEX x TERRAIN_SIZEY x TERRAIN_SIZEZ) array size, at a given 3d index in the world
(first terrain is at (0;0;0), left terrain (-1;0;0))

Every terrain are saved in an hashmap

MESH_PER_TERRAIN meshes are built for each terrain.
Each meshes has a vbo which is filled with every visible face from a subdivision of the terrain's block array
(TERRAIN_SIZEX x (TERRAIN_SIZEY / MESH_PER_TERRAIN) x TERRAIN_SIZEZ) blocks in a mesh

Only faces in camera frustum, and close enough (CHUNK_RENDER_DISTANCE Terrains distance) are rendered (see const.h)




** Extern library used:
openGL
glfw
glew (windows only)
tinycthread.c tinycthread.h
lodepng.c lodepng.h
