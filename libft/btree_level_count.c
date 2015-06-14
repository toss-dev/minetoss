/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 11:51:50 by rpereira          #+#    #+#             */
/*   Updated: 2014/12/29 17:53:23 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		btree_level_count(t_btree *root)
{
	int	r;
	int	l;

	if (root == NULL)
		return (0);
	r = (root->right == 0) ? 0 : 1 + btree_level_count(root->right);
	l = (root->left == 0) ? 0 : 1 + btree_level_count(root->left);
	return (l > r ? l : r);
}
