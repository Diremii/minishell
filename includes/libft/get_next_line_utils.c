/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:40:57 by humontas          #+#    #+#             */
/*   Updated: 2025/01/14 14:48:35 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen_gnl((char *)s1);
	j = ft_strlen_gnl((char *)s2);
	str = malloc((i + j + 1) * sizeof (char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (c < 0 || c >= 127)
		c = c % 128;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc_gnl(int nmemb, int size)
{
	void	*tab;
	int		i;
	int		total_size;

	total_size = nmemb * size;
	if (total_size < 0 || ((int)nmemb < 0 && (int)size < 0))
		return (NULL);
	tab = malloc(nmemb * size);
	if (tab)
	{
		i = 0;
		while (i < total_size)
		{
			*(unsigned char *)(tab + i) = '\0';
			i++;
		}
	}
	return (tab);
}
