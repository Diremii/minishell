/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbaseuint_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:37:32 by ttremel           #+#    #+#             */
/*   Updated: 2024/11/01 13:55:13 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putbaseuint_fd(unsigned int n, const char *base, int fd)
{
	if (n > ft_strlenf(base) - 1)
	{
		ft_putbaseuint_fd(n / ft_strlenf(base), base, fd);
		ft_putbaseuint_fd(n % ft_strlenf(base), base, fd);
	}
	else
		ft_putchar_fd(base[n], fd);
}
