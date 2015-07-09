/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 11:21:23 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 05:03:35 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define ABS(x) ((x) > 0 ? (x) : -(x))
# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define SIGN(x) ((x) < 0 ? (-1) : (1))

# define BUFF_SIZE 8192

# include <errno.h>
# include <sys/ioctl.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <float.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <wchar.h>
# include "color.h"
# include "lodepng.h"
# include "logger.h"

typedef void		(*t_function)();
typedef int 		(*t_cmp_func) (void const *a, void const *b);


/**************************************************************************/
/*                              LINKED LIST                               */
/**************************************************************************/

typedef int 		(*t_iter_function) (void *data, void *extra);

typedef struct		s_node
{
	void			*content;
	struct s_node	*next;
	struct s_node	*previous;
}					t_node;

typedef struct		s_list
{
	t_node	*head;
	size_t	size;
}					t_list;

void				*list_push(t_list *lst, void const *content, size_t content_size);
void				*list_add(t_list *lst, void const *content, size_t content_size);
void 				*list_get(t_list *lst, t_cmp_func cmpf, void *cmpd);
void 				list_iter_remove_if(t_list *lst, t_iter_function iterf, void *extra, t_function free_funct);
void 				list_iter(t_list *lst, t_iter_function iterf, void *extra);
t_list				list_new(void);
int 				list_remove(t_list *lst, t_function free_funct, t_cmp_func cmpf, void *cmpd);
void				list_remove_node(t_list *lst, t_node *node, t_function free_funct);
void				list_delete(t_list *lst, void (*delete_node)(void *content));

/******************************* LINKED LIST END *******************************/



/**************************************************************************/
/*                              HASH MAP                                  */
/**************************************************************************/

typedef struct		s_htab_elem
{
	void	*content;
	char	*key;
}					t_htab_elem;

typedef struct		s_htab
{
	t_list	*elems;
	size_t	size;
}					t_htab;

size_t				htab_hash(char *str, size_t size);
void				*htab_insert(t_htab tab, char *key, void *d, size_t s);
t_htab				htab_new(size_t size);
void				*htab_get(t_htab tab, char *key);
void				htab_delete(t_htab *tab, void (*ft_free)());
void				htab_iter(t_htab tab, t_iter_function f, void *extra);
int					htab_remove_key(t_htab tab, char *key, t_function free_funct);
void				htab_dump_memory(t_htab tab);

/******************************* HASH MAP END ************************************/



/**************************************************************************/
/*                              ARRAY LIST                                */
/**************************************************************************/

typedef int 		(*t_iter_array_function) (void *data, void *extra, unsigned idx);

enum e_array_list_buffer_type
{
	ARRAY_LIST_RDONLY,
	ARRAY_LIST_RDWR
};

typedef struct		s_array_list
{
	char 		*data;
	unsigned	capacity;
	unsigned	size;
	unsigned	elem_size;
	unsigned 	default_capacity;
}					t_array_list;

t_array_list		array_list_new(unsigned nb, unsigned elem_size);
void				array_list_add(t_array_list *array, void *data);
void				array_list_iter(t_array_list array, t_iter_array_function f, void *extra);
void				array_list_iter_remove_if(t_array_list *array, t_iter_array_function f, void *extra);
void 				array_list_delete(t_array_list *array);
void				array_list_resize(t_array_list *array, unsigned size);
void				array_list_remove(t_array_list *array, unsigned int idx);
void 				array_list_sort(t_array_list array, int (*cmpf)(void const *, void const *));
void				array_list_clear(t_array_list *array);
void 				array_list_expand(t_array_list *array);
void				array_list_add_all(t_array_list *array, void *buffer, unsigned nb);
void				*array_list_to_buffer(t_array_list array, unsigned type);
void				array_list_remove_if(t_array_list *array, t_cmp_func cmpf, void *extra);

/******************************  ARRAY LIST END *********************************/



/**************************************************************************/
/*                              BINARY TREE                               */
/**************************************************************************/

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

t_btree				*btree_create_node(void *item);
void				btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void				btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void				btree_insert_data(t_btree **root, void *item,
					int (*cmpf)(void*, void*));
void				*btree_search_item(t_btree *root, void *data_ref,
					int (*cmpf)(void*, void*));
int					btree_level_count(t_btree *root);

/*************************** BINARY TREE END *********************************/


/** rand utils */
float				rand_float_in_range(float min, float max);
int 				rand_in_range(int min, int max);
int 				rand_int(int max);


/** memory related functions */
void				*ft_memdup(const void* d, size_t s);

/** string array functions */
int					ft_strsplit_size(char **tab);
int					ft_strsplit_contains(char **tab, char *sequence);
void				ft_strsplit_free(char **tab);
char				**ft_strsplit(char const *s, char c);
void				ft_swip_strsplit(char **tab, int from, int amount);
char				**ft_strsplit_whitespaces(char const *s);

/** string functions */
char				*ft_strrev(char *str);
char				*ft_strtrim(char const *s);

int					ft_match(char *s1, char *s2);

void				ft_sleep(unsigned int us);

#endif
