/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpereira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 10:50:23 by rpereira          #+#    #+#             */
/*   Updated: 2015/06/04 17:40:34 by rpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void* d, size_t s)
{ 
   void	*p;
    
   p = malloc(s);
   if (p == NULL)
   {
	   return (NULL);
   }
   return (memcpy(p, d, s));
}
