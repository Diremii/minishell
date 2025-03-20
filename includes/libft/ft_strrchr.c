/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:30:16 by humontas          #+#    #+#             */
/*   Updated: 2024/10/16 09:41:59 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	if (c < 0 || c >= 127)
		c = c % 128;
	if (c == '\0')
	{
		i = ft_strlen(s);
		return ((char *)(&s[i]));
	}
	i = ft_strlen(s) - 1;
	while (i != -1)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
