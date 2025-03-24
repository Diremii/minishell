/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:48:39 by ttremel           #+#    #+#             */
/*   Updated: 2024/10/17 17:13:31 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_count(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		n = -n;
		size++;
	}
	if (n == 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size_str;
	size_t	issigned;
	char	*str;

	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	size_str = num_count(n);
	issigned = (n < 0);
	n = (n * -1 * (n < 0) + n * (n >= 0));
	str = (char *)malloc((size_str + 1) * sizeof(char));
	if (!str)
		return (0);
	ft_bzero(str, size_str + 1);
	while (size_str--)
	{
		str[size_str] = '0' + (n % 10);
		n /= 10;
	}
	if (issigned)
		str[0] = '-';
	return (str);
}
