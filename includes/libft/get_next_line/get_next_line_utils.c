/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:48:33 by ttremel           #+#    #+#             */
/*   Updated: 2024/12/10 15:28:47 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (src[size] != '\0')
		size++;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (size);
}

size_t	strclen(const char *str, char c)
{
	const char	*tmp;

	tmp = str;
	if (!str)
		return (0);
	while (*str && *str != c)
		str++;
	if (*str == c)
		return ((str - tmp) + 1);
	return (str - tmp);
}
