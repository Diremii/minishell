/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sovietguy <sovietguy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:06 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/19 19:32:18 by sovietguy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sanitize_line(char *line)
{
	t_data	*data;
	char	*new_line;

	if (!line)
		return (NULL);
	data = get_data(NULL);
	new_line = replace_dollar_in_str(line, data);
	free(line);
	if (!new_line)
		return (NULL);
	return (new_line);
}

static int	create_here_doc(int fd, char *lim)
{
	size_t	lim_size;
	char	*line;

	line = NULL;
	lim_size = ft_strlen(lim);
	while (1)
	{
		ft_printf_fd("here_doc> ", 2);
		line = get_next_line(0);
		line = sanitize_line(line);
		if (!line)
		{
			close(fd);
			return (-1);
		}
		line[ft_strlen(line) - 1] = 0;
		if (ft_strncmp(lim, line, lim_size + 1) == 0)
			break ;
		ft_printf_fd("%s\n", fd, line);
		free(line);
	}
	free(line);
	return (0);
}

int	here_doc(char *lim)
{
	int		fd[2];
	char	*file;

	file = "./.nfs0000000000";
	if (access(file, F_OK) != -1)
		unlink(file);
	fd[0] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[0] == -1)
		return (-1);
	if (create_here_doc(fd[0], lim) == -1)
		return (-1);
	close(fd[0]);
	fd[1] = open(file, O_RDONLY, 0777);
	if (fd[1] == -1)
		return (-1);
	unlink(file);
	return (fd[1]);
}
