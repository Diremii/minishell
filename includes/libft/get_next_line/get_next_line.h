/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:45:24 by ttremel           #+#    #+#             */
/*   Updated: 2025/02/10 12:01:31 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include "../libft.h"

size_t	gnl_strlcpy(char *dest, const char *src, size_t n);
size_t	strclen(const char *str, char c);
char	*get_next_line(int fd);

#endif