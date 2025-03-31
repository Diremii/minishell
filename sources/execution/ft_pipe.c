/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:28:42 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/28 15:18:42 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	here_doc(t_data *data)
{
	int		fd[2];
	char	*file;
	int		rand_num;

	file = "./.nfs0000000000";
	fd[0] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[0] == -1)
		return (-1);
	if (create_here_doc(fd[0], data->cmd->limiter) == -1)
		return (-1);
	close(fd[0]);
	fd[1] = open(file, O_RDONLY, 0777);
	if (fd[1] == -1)
		return (-1);
	unlink(file);
	return (fd[1]);
}

static int	open_fd(int fd[2], t_data *data)
{
	int		ret;

	if (data->cmd->here_doc)
		ret = here_doc(data);
	else
		ret = open(data->cmd->infile, O_RDONLY, 0777);
	fd[0] = ret;
	if (data->cmd->append)
		ret = open(data->cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		ret = open(data->cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd[1] = ret;
	return (0);
}


int	exec_pipe(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	if (open_fd(fd, data) == -1)
		return (-1);
	pid = pipex(data, fd);
	close_fd(fd);
	wait_all_pid(pid);
}
