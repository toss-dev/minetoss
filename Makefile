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

CC = gcc
FLAGS	= -Wall -Wextra -Werror -g3

CLIENT 			= client
SERVER 			= server

CLT_SRC	= main.c \
		  blocks/block.c \
		  blocks/block_texture.c \
		  blocks/raytracing.c \
		  core/args.c \
		  core/game.c \
		  core/game_loop.c \
		  core/game_exit.c \
		  event/event.c \
		  event/key.c \
		  event/mouse.c \
		  event/camera_control.c \
		  event/window.c \
		  network/client.c \
		  network/network.c \
		  network/packet/connection.c \
		  network/packet/live.c \
		  render/camera.c \
		  render/render.c \
		  render/render_ingame.c \
		  render/renderer/render_terrain.c \
		  render/renderer/render_ui.c \
		  render/renderer/render_sky.c \
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
		  render/gui/view.c \
		  render/gui/main_menu.c \
		  render/voxel_model/voxel_model.c \
		  render/voxel_model/render_voxel_model.c \
		  sound/sound.c \
		  sound/sound_util.c \
		  world/setblock.c \
		  world/terrain.c \
		  world/terrain_utils.c \
		  world/terrain_generator.c \
		  world/noise.c \
		  world/world.c

CLT_SRCS	= $(addprefix ./src/client/, $(CLT_SRC))
CLT_OBJ		= $(CLT_SRCS:.c=.o)

SRV_SRC = main.c \
		  game.c \
		  network/network.c \
		  network/server.c \
		  network/packet/live.c
SRV_SRCS 	= $(addprefix ./src/server/, $(SRV_SRC))
SRV_OBJ		= $(SRV_SRCS:.c=.o)



COMMON_SRC 	= network/packet.c timer/timer.c
COMMON_SRCS	= $(addprefix ./src/common/, $(COMMON_SRC))
COMMON_OBJ 	= $(COMMON_SRCS:.c=.o)


LIBFT_DIR 	= ./lib/libft
LIBMATH_DIR = ./lib/maths
LIBFT	= $(LIBFT_DIR)/libft.a
LIBMATH	= $(LIBMATH_DIR)/libft_maths.a

INC		= -I ./includes \
		  -I $(LIBFT_DIR) \
		  -I $(LIBMATH_DIR)


ifeq ($(OS),Darwin)
	LIBGLFW = ./glfw/src/libglfw3.a
	LIB_CLT = $(LIBGLFW) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lopenal
	INC += -I ./glfw/include
endif

ifeq ($(OS),Windows_NT)
	LIB_CLT = -L./lib/win/ -lglfw3 -lgdi32 -lglew32 -lopengl32 -lopenal
	LIBGLFW = ./lib/win/libglw.a
	DLLS_CLIENT = glew32.dll glew32mx.dll
endif

LIB_CLT += $(LIBFT) $(LIBMATH)

LIB_SRV = $(LIBFT) $(LIBMATH)

all: $(DLLS_CLIENT) $(CLIENT) $(SERVER)

$(CLIENT): $(LIBFT) $(LIBMATH) $(COMMON_OBJ) $(CLT_OBJ)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLT_OBJ) $(COMMON_OBJ) $(LIB_CLT)

$(SERVER): $(LIBFT) $(LIBMATH) $(COMMON_OBJ) $(SRV_OBJ)
	$(CC) $(FLAGS) -o $(SERVER) $(SRV_OBJ) $(COMMON_OBJ) $(LIB_SRV)

%.dll:
	cp ./bin/$@ .

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

./glfw/src/libglfw3.a:
	git submodule init glfw
	git submodule update glfw
	cd glfw ; cmake . ; make

$(LIBMATH):
	make -C $(LIBMATH_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(CLT_OBJ)
	rm -rf $(SRV_OBJ)
	rm -rf $(COMMON_OBJ)

fclean: clean
	-rm client.exe.stackdump
	-rm $(DLLS_CLIENT)
	-rm gmon.out
	rm -rf $(CLIENT)
	rm -rf $(SERVER)

fcleanlib:
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBMATH_DIR) fclean

re: fclean all

help:
	@echo "Rules available are:"
	@echo "\t- all: build the whole project"
	@echo "\t- lib: only build libraries"
	@echo "\t- clean: remove object files but keep runnable files and libraries"
	@echo "\t- fclean: remove every binary files and archives"
	@echo "\t- re: fclean the project and build it"

