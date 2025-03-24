/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:40:24 by ttremel           #+#    #+#             */
/*   Updated: 2024/10/17 17:18:34 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_little;

	if (!big && len == 0)
		return (0);
	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	len_little = ft_strlen(little);
	while (big[i] != '\0' && (i + len_little - 1) < len)
	{
		if (ft_strncmp((char *)&big[i], little, len_little) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
