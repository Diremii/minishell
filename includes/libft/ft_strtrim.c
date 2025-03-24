/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:41:37 by ttremel           #+#    #+#             */
/*   Updated: 2024/12/10 16:54:26 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len_s1;
	char	*str;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len_s1 = ft_strlen(s1);
	while (s1[i] && is_in_set(set, s1[i]))
		i++;
	if (!s1[i])
	{
		str = (char *)malloc(1 * sizeof(char));
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	while (is_in_set(set, s1[len_s1 - 1]))
		len_s1--;
	str = ft_strndup((char *)&s1[i], len_s1 - i);
	if (!str)
		return (0);
	return (str);
}
