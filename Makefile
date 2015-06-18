# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpereira <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/15 16:35:51 by rpereira          #+#    #+#              #
#    Updated: 2015/06/14 23:58:10 by rpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = render

HEADER	= ./includes/main.h ./includes/opengl.h \
		  ./includes/blocks.h ./includes/const.h \
		  ./includes/timer.h ./includes/const.h \
		  ./includes/font.h

SRC_DIR	= ./src/

SRC		= blocks/block.c \
		  blocks/raytracing.c \
		  core/main.c \
		  core/args.c \
		  core/game.c \
		  core/game_loop.c \
		  core/game_clean.c \
		  core/thread.c \
		  event/event.c \
		  event/key.c \
		  event/mouse.c \
		  event/camera_control.c \
		  event/window.c \
		  render/camera.c \
		  render/render.c \
		  render/renderer/render_terrain.c \
		  render/renderer/render_particles.c \
		  render/renderer/render_ui.c \
		  render/renderer/render_sky.c \
		  render/renderer/renderer_update.c \
		  render/particles/particles.c \
		  render/particles/texture.c \
		  render/particles/particles_update.c \
		  render/texture/png_parser.c \
		  render/texture/bmp_parser.c \
		  render/terrain/terrain_mesh.c \
		  render/terrain/mesh.c \
		  render/weather/sky.c \
		  render/weather/skycolor.c \
		  render/weather/weather.c \
		  render/font/render_font.c \
		  render/font/font.c \
		  render/opengl/gl_helper.c \
		  render/opengl/program.c \
		  render/opengl/shader.c \
		  render/opengl/vertex.c \
		  render/opengl/model.c \
		  render/opengl/uniforms.c \
		  timer/timer.c \
		  sound/sound.c \
		  world/setblock.c \
		  world/terrain.c \
		  world/terrain_utils.c \
		  world/terrain_generator.c \
		  world/world.c

SRCS	= $(addprefix $(SRC_DIR), $(SRC))
OBJ		= $(SRCS:.c=.o)

LIBFT_DIR	= ./lib/libft
LIBMATH_DIR	= ./lib/maths
LIBFT	= $(LIBFT_DIR)/libft.a
LIBMATH	= $(LIBMATH_DIR)/libft_maths.a

UNAME_S = $(shell uname -s)


INC		= -I ./includes \
		  -I $(LIBFT_DIR) \
		  -I $(LIBMATH_DIR) \
		  -I ./glfw/include

CC = gcc
MAKE_CMD = make
CMAKE_CMD = cmake

ifeq ($(UNAME_S),Darwin)
	LIBGLFW = ./glfw/src/libglfw3.a
	LIB = $(LIBGLFW) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif

ifeq ($(OS),Windows_NT)
	LIB = -lglfw3 -lgdi32 -lglew32 ./lib/libglew32.dll.a -lopengl32
	CC = x86_64-w64-mingw32-gcc
endif

LIB += $(LIBFT) $(LIBMATH)

FLAGS	= -Wall -Wextra -Werror -pg

FLAGS_OPTI = -Ofast

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMATH) $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

./glfw/src/libglfw3.a:
	git submodule init glfw
	git submodule update glfw
	cd glfw ; $(CMAKE_CMD) . ; $(MAKE_CMD)

$(LIBMATH):
	$(MAKE_CMD) -C $(LIBMATH_DIR)

$(LIBFT):
	$(MAKE_CMD) -C $(LIBFT_DIR)

cleanlib:
	$(MAKE_CMD) -C $(LIBFT_DIR) clean
	$(MAKE_CMD) -C $(LIBMATH_DIR) clean

fcleanlib:
	$(MAKE_CMD) -C $(LIBFT_DIR) fclean
	$(MAKE_CMD) -C $(LIBMATH_DIR) fclean

clean: cleanlib
	rm -rf $(OBJ)

fclean: fcleanlib clean
	-rm ./glew32.dll
	-rm ./glew32mx.dll
	-rm ./glfw3.dll
	-rm render.exe.stackdump
	rm -rf $(NAME)

re: fclean all

help:
	@echo "Rules available are:"
	@echo "\t- all: build the whole project"
	@echo "\t- lib: only build libraries"
	@echo "\t- clean: remove object files but keep runnable files and libraries"
	@echo "\t- fclean: remove every binary files and archives"
	@echo "\t- re: fclean the project and build it"

