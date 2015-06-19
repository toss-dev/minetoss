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


INC		= -I ./includes \
		  -I $(LIBFT_DIR) \
		  -I $(LIBMATH_DIR) \
		  -I ./glfw/include

include cc.make
include lib.make

LIB += $(LIBFT) $(LIBMATH)

FLAGS	= -Wall -Wextra -Werror -pg

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMATH) $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c $(HEADER)
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
	rm -rf $(OBJ)

fclean: fcleanlib clean
	-rm render.exe.stackdump
	-rm gmon.out
	rm -rf $(NAME)

re: fclean all

help:
	@echo "Rules available are:"
	@echo "\t- all: build the whole project"
	@echo "\t- lib: only build libraries"
	@echo "\t- clean: remove object files but keep runnable files and libraries"
	@echo "\t- fclean: remove every binary files and archives"
	@echo "\t- re: fclean the project and build it"

