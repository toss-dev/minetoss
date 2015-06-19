# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 14:24:15 by rpereira          #+#    #+#              #
#    Updated: 2015/06/04 18:38:39 by rpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft_maths.a
SRCS	= matrix_op.c \
		  matrix_projection.c matrix_transformation.c \
		  matrix_utils.c cos_sin.c \
		  vec2.c vec3.c point2.c point3.c \
		  math_utils.c triangles.c maths.c

OBJ		= $(SRCS:.c=.o)
INC		= -I ../libft/

include ../../cc.make

FLAGS	= -Wall -Werror -Wextra -Ofast

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $< $(INC)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
