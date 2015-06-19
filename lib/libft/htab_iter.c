/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htab_iter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/04 20:11:02 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/05 03:22:16 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_iter_extra
{
	void			*extra;
	t_iter_function	f;
}				t_iter_extra;

/**
**	Iterate though the hashtable
**
**	Elements should not be remove while iterated on, else way, segfault
*/
static void	list_iter_htab(t_htab_elem *elem, t_iter_extra *iter_extra)
{
	iter_extra->f(elem->content, iter_extra->extra);
}

void		htab_iter(t_htab tab, t_iter_function f, void *extra)
{
	t_iter_extra	iter_extra;
	t_list			*lst;
	size_t			i;

	i = 0;
	iter_extra.extra = extra;
	iter_extra.f = f;
	while (i < tab.size)
	{
		lst = tab.elems + i;
		if (lst != NULL)
		{
			list_iter(lst, (t_iter_function)list_iter_htab, &iter_extra);
		}
		i++;
	}
}
