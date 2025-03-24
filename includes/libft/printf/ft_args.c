/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:54:33 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/03 14:05:20 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	count_arg(const char *format)
{
	size_t	num;
	size_t	i;

	num = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			num++;
			i += 2;
		}
		else
			i++;
	}
	return (num);
}

size_t	size_arg(char format, void *value)
{
	size_t	size;

	size = 0;
	if (format == 'c')
		size = 1;
	if (format == 's')
		size = ft_strlenf((char *)value);
	if (format == 'p')
		size = ft_sizeaddress((size_t)(intptr_t)value);
	if (format == 'd' || format == 'i')
		size = ft_num_count((int)(intptr_t)value);
	if (format == 'u')
		size = ft_uint_count((unsigned int)(intptr_t)value);
	if (format == 'x' || format == 'X')
		size = ft_ubase_count((unsigned int)(intptr_t)value, 16);
	if (format == '%')
		size = 1;
	return (size);
}

void	put_arg(char format, void *value, int fd)
{
	if (format == 'c')
		ft_putchar_fd((char)(intptr_t)value, fd);
	if (format == 's')
		ft_putstr_fd((char *)value, fd);
	if (format == 'p')
		ft_putaddress_fd((size_t)(intptr_t)value, fd);
	if (format == 'd' || format == 'i')
		ft_putnbr_fd((int)(intptr_t)value, fd);
	if (format == 'u')
		ft_putuint_fd((unsigned int)(intptr_t)value, fd);
	if (format == 'x')
		ft_putbaseuint_fd((unsigned int)(intptr_t)value,
			"0123456789abcdef", fd);
	if (format == 'X')
		ft_putbaseuint_fd((unsigned int)(intptr_t)value,
			"0123456789ABCDEF", fd);
	if (format == '%')
		ft_putchar_fd('%', fd);
}
