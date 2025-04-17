/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:32:38 by humontas          #+#    #+#             */
/*   Updated: 2025/04/17 13:34:05 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strccmp(char *s1, char *s2, char c)
{
	char	*str1;
	char	*str2;
	size_t			i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str1 = ft_strndup(s1, strclen(s1, c) - 1);
	str2 = ft_strndup(s2, strclen(s2, c) - 1);
	if (!str1 || !str2)
	{
		free(str1);
		free(str2);
		return (-1);
	}
	while ((str1[i] != '\0' && str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	i = str1[i] - str2[i];
	free(str1);
	free(str2);
	return (i);
}
