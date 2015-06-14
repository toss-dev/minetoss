/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <rpereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 10:03:09 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/07 16:56:33 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_node	*new_node(void const *content, size_t content_size)
{
	t_node	*node;

	if ((node = (t_node*)malloc(sizeof(t_node))) == NULL)
		return (NULL);
	if ((node->content = malloc(content_size)) == NULL)
	{
		free(node);
		return (NULL);
	}
	memcpy(node->content, content, content_size);
	node->content_size = content_size;
	node->next = NULL;
	return (node);
}

void	*list_to_array(t_list lst, size_t size)
{
	t_node			*tmp;
	unsigned char	*array;
	size_t			copied;

	if (size == 0)
		return (NULL);
	if ((array = malloc(size)) == NULL)
		return (NULL);
	copied = 0;
	tmp = lst.begin;
	while (tmp && copied + tmp->content_size <= size)
	{
		memcpy(array + copied, tmp->content, tmp->content_size);
		copied += tmp->content_size;
		tmp = tmp->next;
	}
	return (array);
}

void	*list_push(t_list *lst, void const *content, size_t content_size)
{
	t_node	*end;

	if (lst == NULL)
		return (NULL);
	if ((end = new_node(content, content_size)) == NULL)
		return (NULL);
	if (lst->begin == NULL)
	{
		lst->begin = end;
	}
	if (lst->end == NULL)
	{
		lst->end = end;
	}
	else
	{
		lst->end->next = end;
		lst->end = end;
	}
	lst->size++;
	return (end->content);
}

/** return a pointer to the added data */
void	*list_add(t_list *lst, void const *content, size_t content_size)
{
	t_node	*n;

	if (lst == NULL)
		return (NULL);
	n = new_node(content, content_size);
	if (n == NULL)
		return (NULL);
	n->next = lst->begin;
	lst->begin = n;
	if (lst->end == NULL)
	{
		lst->end = lst->begin;
	}
	lst->size++;
	return (n->content);
}

/** iterate on the list */
void	list_iter(t_list *lst, t_iter_function f, void *extra)
{
	t_node	*tmp;

	tmp = lst->begin;
	while (tmp)
	{
		f(tmp->content, extra);
		tmp = tmp->next;
	}
}

/** remove if the comparison return elements are equals (works like strcmp) */
bool	list_remove_if(t_list *lst, t_function free_funct, t_cmp_func cmpf, void *cmpd)
{
	t_node	*tmp;
	t_node	*prev;

	if (lst == NULL)
		return (false);
	prev = NULL;
	tmp = lst->begin;
	while (tmp)
	{
		if (cmpf(tmp->content, cmpd) == 0)
		{
			if (prev == NULL)
			{
				lst->begin = tmp->next;
				free_funct(tmp->content);
				free(tmp);
				tmp = lst->begin;
			}
			else
			{
				prev->next = tmp->next;
				free(tmp->content);
				free(tmp);
				tmp = prev->next;
			}
			lst->size--;
			return (true);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (false);
}

/** iterate on the list, and remove the current node if the called function returns false */
void	list_iter_remove_if(t_list *lst, t_iter_function f, void *extra)
{
	t_node	*tmp;
	t_node	*prev;

	if (lst == NULL)
		return ;
	prev = NULL;
	tmp = lst->begin;
	while (tmp)
	{
		if (f(tmp->content, extra))
		{
			if (prev == NULL)
			{
				lst->begin = tmp->next;
				free(tmp->content);
				free(tmp);
				tmp = lst->begin;
			}
			else
			{
				prev->next = tmp->next;
				free(tmp->content);
				free(tmp);
				tmp = prev->next;
			}
			lst->size--;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

t_list	list_new(void)
{
	t_list	list;

	list.begin = NULL;
	list.end = NULL;
	list.size = 0;
	return (list);
}

void	list_delete(t_list *lst, void (*delete_node)(void *content))
{
	t_node	*tmp;
	t_node	*next;

	if (delete_node == NULL)
		delete_node = free;
	tmp = lst->begin;
	while (tmp)
	{
		next = tmp->next;
		delete_node(tmp->content);
		free(tmp);
		tmp = next;
	}
	lst->size = 0;
	lst->begin = NULL;
	lst->end = NULL;
}
