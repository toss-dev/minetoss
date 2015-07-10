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

CLIENT 	= client
SERVER 	= server

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
		  render/camera.c \
		  render/render.c \
		  render/renderer/render_terrain.c \
		  render/renderer/render_particles.c \
		  render/renderer/render_ui.c \
		  render/renderer/render_sky.c \
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
		  network/server.c

SRV_SRCS	= $(addprefix ./src/server/, $(SRV_SRC))
SRV_OBJ	= $(SRV_SRCS:.c=.o)

COMMON_SRC 	= network/packet.c

COMMON_SRCS	= $(addprefix ./src/common/, $(COMMON_SRC))
COMMON_OBJ 	= $(COMMON_SRCS:.c=.o)

LIBFT_DIR	= ./lib/libft
LIBMATH_DIR	= ./lib/maths
LIBFT	= $(LIBFT_DIR)/libft.a
LIBMATH	= $(LIBMATH_DIR)/libft_maths.a


INC		= -I ./includes \
		  -I $(LIBFT_DIR) \
		  -I $(LIBMATH_DIR) \
		  -I ./glfw/include

include cc.make
include lib.make

LIB += $(LIBFT) $(LIBMATH)

FLAGS	= -Wall -Wextra -Werror -g3

all: $(CLIENT) $(SERVER) $(DB)

$(CLIENT): $(LIBFT) $(LIBMATH) $(COMMON_OBJ) $(CLT_OBJ)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLT_OBJ) $(COMMON_OBJ) $(LIB)

$(SERVER): $(LIBFT) $(LIBMATH) $(COMMON_OBJ) $(SRV_OBJ)
	$(CC) $(FLAGS) -o $(SERVER) $(SRV_OBJ) $(COMMON_OBJ) $(LIB)

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

cleanlib:
	make -C $(LIBFT_DIR) clean
	make -C $(LIBMATH_DIR) clean

fcleanlib:
	make -C $(LIBFT_DIR) fclean
	make -C $(LIBMATH_DIR) fclean

clean: cleanlib
	rm -rf $(CLT_OBJ)
	rm -rf $(SRV_OBJ)
	rm -rf $(COMMON_OBJ)

fclean: fcleanlib clean
	-rm render.exe.stackdump
	-rm gmon.out
	rm -rf $(CLIENT)
	rm -rf $(SERVER)

re: fclean all

help:
	@echo "Rules available are:"
	@echo "\t- all: build the whole project"
	@echo "\t- lib: only build libraries"
	@echo "\t- clean: remove object files but keep runnable files and libraries"
	@echo "\t- fclean: remove every binary files and archives"
	@echo "\t- re: fclean the project and build it"

