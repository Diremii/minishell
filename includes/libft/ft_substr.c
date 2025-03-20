/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:36:53 by humontas          #+#    #+#             */
/*   Updated: 2024/10/18 09:06:14 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	i;
	size_t	s_len;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	i = 0;
	array = malloc((len + 1) * sizeof (char));
	if (!array)
		return (NULL);
	while (s[start] && i < len)
	{
		array[i] = s[start];
		i++;
		start++;
	}
	array[i] = '\0';
	return (array);
}
