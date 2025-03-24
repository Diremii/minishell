/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:10:12 by ttremel           #+#    #+#             */
/*   Updated: 2024/12/11 13:08:22 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join(char **strs, char *sep, size_t size)
{
	char		*joined_str;
	size_t		t_size;
	size_t		i;

	if (!sep || !strs)
		return (0);
	i = -1;
	t_size = ft_strlen(sep) * size;
	while (++i < size)
		t_size += ft_strlen(strs[i]);
	joined_str = (char *)malloc((t_size + 1) * sizeof(char));
	if (!joined_str)
		return (0);
	ft_bzero(joined_str, t_size + 1);
	if (size == 0)
		return (joined_str);
	i = -1;
	while (++i < size)
	{
		ft_strcat(joined_str, strs[i]);
		if (i < size - 1)
			ft_strcat(joined_str, sep);
	}
	return (joined_str);
}
