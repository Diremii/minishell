/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:04:36 by humontas          #+#    #+#             */
/*   Updated: 2024/10/18 09:05:28 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tab;
	long int		i;

	i = nmemb * size;
	if (i < 0 || ((int)nmemb < 0 && (int)size < 0))
		return (NULL);
	tab = malloc(nmemb * size);
	if (tab)
		ft_memset(tab, '\0', nmemb * size);
	return (tab);
}
