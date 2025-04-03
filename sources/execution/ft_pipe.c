/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:28:42 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/03 18:05:29 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec(int fd[2], t_data *data)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (fd[0] != 0)
		{
			dup2(p_fd[0], 0);
			close(p_fd[0]);
		}
		if (fd[1] != 1)
			close(fd[1]);
		execve(data->cmd->cmd_param[0], data->cmd->cmd_param, NULL);
	}
	else
	{
		if (fd[1] != 1)
		{
			dup2(p_fd[1], 1);
			close(p_fd[1]);
		}
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	pid_t	pid;
	int		fd[2];

	if (open_fd(fd, data->cmd))
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		ft_exec(fd, data);
	else
		waitpid(pid, NULL, 0);
	return (0);
}
