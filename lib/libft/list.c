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

t_list	list_new(void)
{
	t_list	list;

	list.head = (t_list_node*)malloc(sizeof(t_list_node));
	list.head->next = list.head;
	list.head->previous = list.head;
	list.size = 0;
	return (list);
}

void	list_remove_node(t_list *lst, t_list_node *node, t_function free_funct)
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

	if (free_funct)
	{
		free_funct(node + 1);
	}
	free(node);
	lst->size--;
}

/** remove list head */
void	list_pop(t_list *lst, t_function free_funct)
{
	if (lst->size > 0)
	{
		list_remove_node(lst, lst->head->next, free_funct);
	}
}

/** return content at the begining of the list */
void	*list_head(t_list *lst)
{
	if (lst->size > 0)
	{
		return (lst->head->next + 1);
	}
	return (NULL);
}


/** remove if the comparison return elements are equals (works like strcmp) */
int 	list_remove(t_list *lst, t_function free_funct, t_cmp_func cmpf, void *cmpd)
{
	t_list_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		if (cmpf(node + 1, cmpd) == 0)
		{
			list_remove_node(lst, node, free_funct);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

/** the content of size content_size is stored just after the node, so only 1 malloc is used */
void 	*list_add(t_list *lst, void const *content, unsigned int content_size)
{
	t_list_node	*node;
	t_list_node	*tmp;

	node = (t_list_node*)malloc(sizeof(t_list_node) + content_size);
	if (node == NULL)
	{
		return (NULL);
	}
	memcpy(node + 1, content, content_size);
	node->content_size = content_size;

	tmp = lst->head->next;

	lst->head->next = node;
	tmp->previous = node;

	node->previous = lst->head;
	node->next = tmp;

	lst->size++;

	return (node + 1);
}

void 	*list_push(t_list *lst, void const *content, unsigned int content_size)
{
	t_list_node	*node;
	t_list_node	*tmp;

	node = (t_list_node*)malloc(sizeof(t_list_node) + content_size);
	if (node == NULL)
	{
		return (NULL);
	}
	memcpy(node + 1, content, content_size);
	node->content_size = content_size;
	
	tmp = lst->head->previous;

	lst->head->previous = node;
	tmp->next = node;

	node->previous = tmp;
	node->next = lst->head;

	lst->size++;

	return (node + 1);
}

/** cmpf is a function which should work like strcmp */
void 	*list_get(t_list *lst, t_cmp_func cmpf, void *cmpd)
{
	t_list_node	*node;

	node = lst->head->next;
	while (node != lst->head)
	{
		if (cmpf(node + 1, cmpd) == 0)
		{
			return (node + 1);
		}
		node = node->next;
	}
	return (NULL);
}

void	list_delete(t_list *lst, void (*delete_content)(void *content))
{
	t_list_node	*node;
	t_list_node	*next;

	node = lst->head->next;
	while (node != lst->head)
	{
		next = node->next;
		if (delete_content)
		{
			delete_content(node + 1);
		}
		free(node);
		node = next;
	}
	free(lst->head);
	lst->head = NULL;
	lst->size = 0;
}

/** write the list to a file descriptor */
//	[S] [S] [S] [S] [C] [C] [C] [C] [D] [D] ... [C] [C] [C] [C]
//	S == list.size
//	C == node.content_size
//	D == node.content
//	return -1 if an error occured, else way 0
int		list_to_fd(t_list *list, int fd)
{
	t_list_node	*node;

	if (write(fd, &(list->size), sizeof(list->size)) <= 0)
	{
		return (-1);
	}
	node = list->head->next;
	while (node != list->head)
	{
		if (write(fd, &(node->content_size), sizeof(node->content_size)) <= 0)
		{
			return (-1);
		}
		if (write(fd, node + 1, node->content_size) <= 0)
		{
			return (-1);
		}
		node = node->next; 
	}
	return (0);
}

/* load a list from the given fildes */
t_list 	list_from_fd(int fd)
{
	char 			*buffer;
	size_t			buffer_size;
	t_list 			lst;
	unsigned int	i;
	unsigned int 	node_content_size;

	lst = list_new();
	if (read(fd, &(lst.size), sizeof(lst.size)) <= 0)
	{
		return (lst);
	}
	buffer_size = 65536;
	buffer = (char*)malloc(buffer_size);
	i = 0;
	while (i < lst.size)
	{
		if (read(fd, &(node_content_size), sizeof(node_content_size)) <= 0)
		{
			break ;
		}
		while (node_content_size >= buffer_size)
		{
			buffer_size = buffer_size * 2;
			buffer = (char*)realloc(buffer, buffer_size);
		}
		if (read(fd, buffer, node_content_size) <= 0)
		{
			break ;
		}
		list_push(&lst, buffer, node_content_size);
		++i;
	}
	free(buffer);
	return (lst);
}