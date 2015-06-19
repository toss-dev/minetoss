/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 10:50:23 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/13 04:48:28 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array_list	array_list_new(unsigned nb, unsigned elem_size)
{
	t_array_list	array;

	array.data = calloc(nb, elem_size);
	array.capacity = nb;
	array.elem_size = elem_size;
	array.size = 0;
	array.default_capacity = nb;
	return (array);
}

void		array_list_add(t_array_list *array, void *data)
{
	if (array->size == array->capacity)
	{
		array_list_expand(array);
	}
	memcpy(array->data + array->size * array->elem_size, data, array->elem_size);
	array->size++;
}

void		array_list_add_all(t_array_list *array, void *buffer, unsigned nb)
{
	unsigned	array_idx;
	unsigned	copy_nb;
	unsigned	copy_size;

	array_idx = array->size * array->elem_size;
	while (nb)
	{
		copy_nb = MIN(array->capacity - array->size, nb);
		if (copy_nb == 0)
		{
			array_list_expand(array);
			continue ;
		}
		copy_size = copy_nb * array->elem_size;
		memcpy(array->data + array_idx, buffer, copy_size);
		nb -= copy_nb;
		array->size += copy_nb;
		buffer += copy_size;
		array_idx += copy_size;
	}
}

void 		array_list_expand(t_array_list *array)
{
	printf("libft warning: expanding array list is bad for performance! (%u => %u)\n",
		array->capacity, array->capacity + array->default_capacity);
	array->data = realloc(array->data, (array->capacity + array->default_capacity) * array->elem_size);
	array->capacity += array->default_capacity;
}

/**
**	get item by index
*/
void		*array_list_get(t_array_list *array, unsigned idx)
{
	return (array->data + idx * array->elem_size);
}

/**
**	swap the removed item with the last one to have defragmented memory
*/
void		array_list_remove(t_array_list *array, unsigned int idx)
{
	memmove(array->data + idx * array->elem_size, array->data + (array->size - 1) * array->elem_size, array->elem_size);
	array->size--;
}

void		array_list_clear(t_array_list *array)
{
	array->size = 0;
}

/** this functions assumes the array is defragmented */
void		array_list_iter(t_array_list array, t_iter_array_function f, void *extra)
{
	unsigned	i;
	unsigned	addr;

	i = 0;
	addr = 0;
	while (i < array.size)
	{
		f(array.data + addr, extra, i);
		addr += array.elem_size;
		++i;
	}
}

void		array_list_remove_if(t_array_list *array, t_cmp_func cmpf, void *extra)
{
	unsigned int	i;
	unsigned int	addr;

	i = 0;
	addr = 0;
	while (i < array->size)
	{
		if (cmpf(array->data + addr, extra))
		{
			array_list_remove(array, i);
			return ;
		}
		else
		{
			addr += array->elem_size;
			++i;
		}
	}
}

/** this functions assumes the array is defragmented */
void		array_list_iter_remove_if(t_array_list *array, t_iter_array_function f, void *extra)
{
	unsigned	i;
	unsigned	addr;

	i = 0;
	addr = 0;
	while (i < array->size)
	{
		if (f(array->data + addr, extra, i))
		{
			array_list_remove(array, i);
		}
		else
		{
			addr += array->elem_size;
			++i;
		}
	}
}

/**
**	remove the array list from the heap
*/
void 		array_list_delete(t_array_list *array)
{
	free(array->data);
	array->data = NULL;
	array->size = 0;
	array->capacity = 0;
}

/**
**	resize array list
*/
void		array_list_resize(t_array_list *array, unsigned size)
{
	array->data = realloc(array->data, size * array->elem_size);
	array->capacity = size;
}

/**
**	sort the array list with the given comparison functin (cf strcmp)
*/
void		array_list_sort(t_array_list array, t_cmp_func cmpf)
{
	qsort(array.data, array.size, array.elem_size, cmpf);
}

/**
**	get a memory buffer for the given array list
**
**	array:	array list
**	type:	ARRAY_BUFFER_RDONLY or ARRAY_BUFFER_RDWR
**/
void		*array_list_to_buffer(t_array_list array, unsigned type)
{
	if (type == ARRAY_LIST_RDONLY)
	{
		return (array.data);
	}
	return (ft_memdup(array.data, array.size * array.elem_size));
}
