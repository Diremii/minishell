/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:06:22 by humontas          #+#    #+#             */
/*   Updated: 2025/01/14 14:49:39 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin_gnl(s1, s2);
	free(s1);
	return (result);
}

static char	*save_remaining_buffer(char *buffer)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remaining = ft_calloc_gnl(ft_strlen_gnl(buffer) - i + 1, sizeof(char));
	if (!remaining)
		return (NULL);
	while (buffer[i])
		remaining[j++] = buffer[i++];
	free(buffer);
	return (remaining);
}

static char	*search_for_newline(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc_gnl(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*read_and_store(int fd, char *result)
{
	char	*buffer;
	int		read_var;

	if (!result)
		result = ft_calloc_gnl(1, sizeof(char));
	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	read_var = 1;
	while (read_var > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		read_var = read(fd, buffer, BUFFER_SIZE);
		if (read_var <= 0 && !result[0])
		{
			free(result);
			free(buffer);
			return (NULL);
		}
		buffer[read_var] = '\0';
		result = join_and_free(result, buffer);
		if (!result)
			break ;
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer || !buffer[0])
	{
		free(buffer);
		return (NULL);
	}
	line = search_for_newline(buffer);
	buffer = save_remaining_buffer(buffer);
	return (line);
}
