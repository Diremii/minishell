/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:13:00 by ttremel           #+#    #+#             */
/*   Updated: 2025/02/14 18:06:05 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			ag;
	size_t			size;
	void			*arg;

	if (!format)
		return (-1);
	size = ft_strlenf(format) - 2 * count_arg(format);
	va_start(ag, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) != '%')
				arg = va_arg(ag, void *);
			put_arg(*(format + 1), arg, 1);
			size += size_arg(*(++format), arg);
			if (*(++format) == '\0')
				break ;
		}
		if (!(*format == '%'))
			ft_putchar_fd(*(format++), 1);
	}
	va_end(ag);
	return (size);
}

int	ft_printf_fd(const char *format, int fd, ...)
{
	va_list			ag;
	size_t			size;
	void			*arg;

	if (!format)
		return (-1);
	size = ft_strlenf(format) - 2 * count_arg(format);
	va_start(ag, fd);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (*(format + 1) != '%')
				arg = va_arg(ag, void *);
			put_arg(*(format + 1), arg, fd);
			size += size_arg(*(++format), arg);
			if (*(++format) == '\0')
				break ;
		}
		if (!(*format == '%'))
			ft_putchar_fd(*(format++), fd);
	}
	va_end(ag);
	return (size);
}
