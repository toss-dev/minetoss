/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 10:18:42 by rpereira          #+#    #+#             */
/*   Updated: 2015/03/23 10:00:06 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*ret;

	ret = (t_btree*)malloc(sizeof(t_btree));
	if (ret == NULL)
		return (NULL);
	ret->item = item;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}
