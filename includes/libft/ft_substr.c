/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:42:35 by ttremel           #+#    #+#             */
/*   Updated: 2024/10/17 17:18:27 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*extract;
	size_t	i;
	size_t	alloc;

	i = 0;
	if (!s || (!len || ft_strlen(s) < start))
	{
		extract = (char *)malloc(1 * sizeof(char));
		if (!extract)
			return (0);
		extract[0] = '\0';
		return (extract);
	}
	alloc = ft_strlen(s) - start;
	if ((!start && len <= ft_strlen(s)) || start + len < ft_strlen(s))
		alloc = len;
	if (!s[start + 1] || (start - len == 1 && len < ft_strlen(s)))
		alloc = 1;
	extract = (char *)malloc((alloc + 1) * sizeof(char));
	if (!extract)
		return (0);
	while (s[start] && i < len)
		extract[i++] = s[start++];
	extract[i] = '\0';
	return (extract);
}
