/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:49:37 by ttremel           #+#    #+#             */
/*   Updated: 2024/10/16 18:03:00 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*occ;
	unsigned char	to_find;

	i = 0;
	to_find = (unsigned char)c;
	occ = (unsigned char *)s;
	while (n--)
	{
		if (occ[i] == to_find)
			return (&occ[i]);
		i++;
	}
	return (0);
}
