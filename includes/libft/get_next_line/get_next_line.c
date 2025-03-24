/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:44:54 by ttremel           #+#    #+#             */
/*   Updated: 2024/12/10 15:29:00 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*filler(char *line, char *buff, size_t n)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!line)
	{
		line = ft_strndup(buff, n);
		return (line);
	}
	str = (char *)malloc((strclen(line, '\0') + n));
	if (!str)
	{
		free(line);
		return (0);
	}
	while (line[i])
		str[j++] = line[i++];
	i = 0;
	while (buff[i] && i < n)
		str[j++] = buff[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

static char	*fill_line(char *buff, char *line, int fd)
{
	size_t			len;
	long long int	num;

	ft_bzero(buff, BUFFER_SIZE);
	while (!ft_strchr(line, '\n'))
	{
		if (!ft_strchr(buff, '\n'))
			num = read(fd, buff, BUFFER_SIZE);
		if (num == -1)
		{
			free(line);
			return (NULL);
		}
		if (!num)
			return (line);
		len = strclen(buff, '\n');
		line = filler(line, buff, len);
		if (!line)
			return (NULL);
		if (!ft_strchr(buff, '\n'))
			ft_bzero(buff, BUFFER_SIZE);
		else
			gnl_strlcpy(buff, buff + len, BUFFER_SIZE - len);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[1024][BUFFER_SIZE] = {0};
	char		*line;
	size_t		len;

	line = NULL;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024)
		return (NULL);
	if (buff[fd][0])
	{
		len = strclen(buff[fd], '\n');
		line = ft_strndup(buff[fd], len);
		if (!line)
			return (0);
		gnl_strlcpy(buff[fd], buff[fd] + len, BUFFER_SIZE - len);
	}
	if (!ft_strchr(line, '\n'))
		line = fill_line(buff[fd], line, fd);
	return (line);
}
