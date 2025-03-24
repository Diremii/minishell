/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:33:30 by ttremel           #+#    #+#             */
/*   Updated: 2024/10/17 17:18:46 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	num_wrd;
	size_t	i;

	num_wrd = 1;
	i = 0;
	while (s && s[i] && s[i] == c)
		i++;
	if (!s || !s[i])
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] == '\0')
				return (num_wrd);
			num_wrd++;
		}
		i++;
	}
	return (num_wrd);
}

static void	free_for_all(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	*ft_strcut(char *str, char c)
{
	char	*dup;
	int		len_str;
	int		i;

	i = 0;
	len_str = 0;
	while (str[len_str] != '\0' && str[len_str] != c)
		len_str++;
	dup = (char *)ft_calloc(len_str + 1, sizeof(char));
	if (!dup)
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

static char	**splitter(char **strs, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	j = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			k = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			strs[j++] = ft_strcut((char *)&s[k], c);
			if (!strs[j - 1])
			{
				free_for_all(strs);
				return (0);
			}
		}
		if (s[i] == '\0')
			break ;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**lst_str;
	size_t	num_wrds;

	if (!s)
		return (0);
	num_wrds = ft_count_words(s, c);
	lst_str = (char **)ft_calloc(num_wrds + 1, sizeof(char *));
	if (!lst_str)
		return (NULL);
	if (!num_wrds)
	{
		lst_str[0] = NULL;
		return (lst_str);
	}
	lst_str = splitter(lst_str, s, c);
	if (!lst_str)
		return (0);
	return (lst_str);
}
