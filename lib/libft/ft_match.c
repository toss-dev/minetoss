/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 18:09:22 by rpereira          #+#    #+#             */
/*   Updated: 2015/04/01 17:33:46 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + ('a' - 'A'));
	}
	return (c);
}

int			ft_match(char *s1, char *s2)
{
	if (*s1 && ft_tolower(*s1) == ft_tolower(*s2) && *s1 != '*')
		return (ft_match(s1 + 1, s2 + 1));
	else if (*s1 && *s2 == '*')
		return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
	else if (*s2 == '*')
		return (ft_match(s1, s2 + 1));
	else if (*s1 == 0 && *s2 == 0)
		return (1);
	else
		return (0);
}
