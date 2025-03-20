/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:04:29 by humontas          #+#    #+#             */
/*   Updated: 2024/10/18 09:10:28 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(const char *s, char c)
{
	int	count;
	int	tmp;

	count = 0;
	tmp = 0;
	while (*s)
	{
		if (*s != c && tmp == 0)
		{
			tmp = 1;
			count++;
		}
		else if (*s == c)
			tmp = 0;
		s++;
	}
	return (count);
}

static char	*ft_fill_word(char *str, int start, int end)
{
	char	*substr;
	int		i;

	i = 0;
	substr = malloc ((end - start + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (start < end)
	{
		substr[i] = str[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static void	*ft_free(char **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**ft_re_split(char **split, const char *s, char c)
{
	size_t	i;
	int		j;
	int		w_split;

	i = 0;
	j = 0;
	w_split = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && w_split < 0)
			w_split = i;
		else if ((s[i] == c || i == ft_strlen(s)) && w_split >= 0)
		{
			split[j] = ft_fill_word((char *)s, w_split, i);
			if (!(split[j]))
				return (ft_free(split, j));
			w_split = -1;
			j++;
		}
		i++;
	}
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = ft_calloc((ft_count_word((char *)s, c) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	split = ft_re_split(split, s, c);
	if (!split)
		return (NULL);
	return (split);
}
