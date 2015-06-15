# minetoss

this | is | a | test
--------------------
test | a | b  | c |

Minecraft like rendering engine to learn openGL


Currently working on the rendering system:

terrain are TERRAIN_SIZEX x TERRAIN_SIZEY x TERRAIN_SIZEZ array size, at a given 3d index in the world
(first terrain is at (0;0;0), left terrain (-1;0;0))

they are saved in an hashmap

MESH_PER_TERRAIN meshes are built, containing every visible face from a subdivision of the terrain's block array
TERRAIN_SIZEX x (TERRAIN_SIZEY / MESH_PER_TERRAIN) x TERRAIN_SIZEZ blocks in a mesh

Only faces in camera frustum (currently 70 fov), and close enough (8 Terrains distance) are rendered (see const.h)




Extern library used:

tinycthread.c tinycthread.h

lodepng.c lodepng.h

modern openGL

glfw

glew (windows only)

