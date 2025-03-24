/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:14:05 by ttremel           #+#    #+#             */
/*   Updated: 2024/11/01 13:52:48 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex_fd(size_t n, int fd)
{
	const char	*base;

	base = "0123456789abcdef";
	if (n > ft_strlenf(base) - 1)
	{
		ft_puthex_fd(n / 16, fd);
		ft_puthex_fd(n % 16, fd);
	}
	else
		ft_putchar_fd(base[n], fd);
}

void	ft_putaddress_fd(size_t n, int fd)
{
	if (!n)
		write(fd, "(nil)", 5);
	else
	{
		write(fd, "0x", 2);
		ft_puthex_fd(n, fd);
	}
}
