/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/13 14:02:02 by rpereira          #+#    #+#             */
/*   Updated: 2014/12/13 14:03:38 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_capitalize(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - ('a' - 'A');
		else if (i > 0 && str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + ('a' - 'A');
		i++;
	}
	return (str);
}
