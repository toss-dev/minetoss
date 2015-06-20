# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/05 14:24:15 by rpereira          #+#    #+#              #

#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_memdup.c ft_strtrim.c ft_epur.c \
		  array_list.c list.c \
		  ft_strsplit_util.c ft_strsplit_whitespaces.c ft_strsplit.c \
		  btree_create_node.c btree_insert_data.c \
		  btree_apply_infix.c btree_apply_prefix.c btree_apply_suffix.c \
		  btree_search_item.c btree_level_count.c \
		  htab.c htab_iter.c \
		  ft_nbrlen.c \
		  ft_match.c rand_utils.c \
		  lodepng.c logger.c bordel.c
OBJ	= $(SRCS:.c=.o)

FLAGS	= -Wall -Werror -Wextra -pg

include ../../cc.make

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
