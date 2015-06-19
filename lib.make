ifeq ($(OS),Darwin)
	LIBGLFW = ./glfw/src/libglfw3.a
	LIB = $(LIBGLFW) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lopenal
endif

ifeq ($(OS),Windows_NT)
	LIB = -L./lib/win/ -lglfw3 -lgdi32 -lglew32 -lopengl32 -lopenal
	LIBGLFW = ./lib/win/libglw.a
endif