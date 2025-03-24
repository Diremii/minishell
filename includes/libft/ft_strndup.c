/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:36:47 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/03 14:00:34 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	char		*dup;
	size_t		i;

	if (!str)
		return (0);
	i = 0;
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (0);
	while (str[i] != '\0' && i < n)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
