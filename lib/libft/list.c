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
/*
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
	node->previous = NULL;
	return (node);
}*/

t_list	list_new(void)
{
	t_list	list;

	list.head = (t_node*)malloc(sizeof(t_node));
	list.head->content = NULL;
	list.head->next = list.head;
	list.head->previous = list.head;
	list.size = 0;
	return (list);
}

static void	list_remove_node(t_list *lst, t_node *node, t_function free_funct)
{
	if (node->previous)
	{
		node->previous->next = node->next;
	}
	if (node->next)
	{
		node->next->previous = node->previous;
	}

	node->next = NULL;
	node->previous = NULL;

	printf("%p\n", node->content);
	free_funct(node->content);
	free(node);
	lst->size--;
}

/** remove if the comparison return elements are equals (works like strcmp) */
int 	list_remove(t_list *lst, t_function free_funct, t_cmp_func cmpf, void *cmpd)
{
	t_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		if (cmpf(node->content, cmpd) == 0)
		{
			list_remove_node(lst, node, free_funct);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void 	list_iter(t_list *lst, t_iter_function iterf, void *extra)
{
	t_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		iterf(node->content, extra);
		node = node->next;
	}
}

void 	*list_add(t_list *lst, void const *content, size_t content_size)
{
	t_node	*node;
	t_node	*tmp;

	node = (t_node*)malloc(sizeof(t_node));
	node->content = ft_memdup(content, content_size);
	
	tmp = lst->head->next;

	lst->head->next = node;
	tmp->previous = node;

	node->previous = lst->head;
	node->next = tmp;

	lst->size++;

	return (node->content);
}

void 	*list_get(t_list *lst, t_cmp_func cmpf, void *cmpd)
{
	t_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		if (cmpf(node->content, cmpd) == 0)
		{
			return (node->content);
		}
		node = node->next;
	}
	return (NULL);
}

void 	*list_push(t_list *lst, void const *content, size_t content_size)
{
	t_node	*node;
	t_node	*tmp;

	node = (t_node*)malloc(sizeof(t_node));
	node->content = ft_memdup(content, content_size);
	
	tmp = lst->head->previous;

	lst->head->previous = node;
	tmp->next = node;

	node->previous = tmp;
	node->next = lst->head;

	lst->size++;

	return (node->content);
}

void	list_delete(t_list *lst, void (*delete_content)(void *content))
{
	t_node	*node;
	t_node	*next;

	node = lst->head->next;
	while (node != lst->head)
	{
		next = node->next;
		delete_content(node->content);
		free(node);
		node = next;
	}
	free(lst->head);
	lst->head = NULL;
	lst->size = 0;
}
