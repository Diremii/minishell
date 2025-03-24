/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:13:38 by ttremel           #+#    #+#             */
/*   Updated: 2025/02/14 17:38:10 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include "../libft.h"

void	ft_putuint_fd(unsigned int n, int fd);
void	ft_putbaseuint_fd(unsigned int n, const char *base, int fd);
void	ft_putaddress_fd(size_t n, int fd);
void	put_arg(char format, void *value, int fd);
size_t	size_arg(char format, void *value);
size_t	count_arg(const char *format);
size_t	ft_strlenf(const char *str);
size_t	ft_num_count(int n);
size_t	ft_uint_count(unsigned int n);
size_t	ft_ubase_count(unsigned int n, int base);
size_t	ft_sizeaddress(size_t n);
int		ft_printf(const char *format, ...);
int		ft_printf_fd(const char *format, int fd, ...);

#endif
