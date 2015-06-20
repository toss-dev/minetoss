# minetoss

Minecraft like engine openGL / GLFW
-----------------------------------------------

• Currently working on the rendering system: (https://github.com/toss-dev/minetoss/blob/master/includes/const.h)

For technical questions, see comments in code :)



TODO:
	- reduce main thread tasks (use for rendering)
	- improve memory managment in terrain generation / deletion
	- create a thread pool for terrain generation (1 thread for rendering, 1 for updating world, 2 for generating world)


--------------------------------------
Extern library used:
* OpenGL (modern pipeline)
* GLFW (opengl framework)
* glew (windows only)
* pthread
* lodepng.c lodepng.h (png decoder / encoder)
