/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:37:02 by ttremel           #+#    #+#             */
/*   Updated: 2024/10/24 12:30:02 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	size_dst;
	size_t	size_src;
	size_t	i;

	size_src = ft_strlen(src);
	if (n == 0)
		return (size_src);
	size_dst = ft_strlen(dest);
	if (size_dst >= n)
		return (size_src + n);
	i = 0;
	while (i < n - size_dst - 1 && src[i] != '\0')
	{
		dest[size_dst + i] = src[i];
		i++;
	}
	dest[size_dst + i] = '\0';
	return (size_dst + size_src);
}
