/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 11:18:45 by rpereira          #+#    #+#             */
/*   Updated: 2015/03/23 18:20:29 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_insert_data(t_btree **root, void *item, int (*cmpf)(void*, void*))
{
	if (root == NULL || item == NULL)
		return ;
	if (*root == NULL)
		*root = btree_create_node(item);
	else
	{
		if (cmpf == NULL)
			return ;
		if (cmpf(item, (*root)->item) > 0)
			btree_insert_data(&(*root)->right, item, cmpf);
		else
			btree_insert_data(&(*root)->left, item, cmpf);
	}
}
