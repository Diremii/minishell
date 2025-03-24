/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:38:11 by ttremel           #+#    #+#             */
/*   Updated: 2024/11/01 13:52:17 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlenf(const char *str)
{
	const char	*tmp;

	tmp = str;
	if (!str)
		return (6);
	while (*str != '\0')
		str++;
	return (str - tmp);
}
