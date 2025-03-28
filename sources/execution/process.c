/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:14:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/06 15:24:59 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	child_process(int p_fd[2], int fd[2], t_cmd ***cmds, int i)
{
	if ((fd[0] == -1 && i == 0))
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close_fd(fd);
		free_for_all(*cmds);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(p_fd[0]);
		if (dup2(p_fd[1], 1) == -1)
			close_all(p_fd, fd, *cmds);
		close(p_fd[1]);
		ft_exec(p_fd, fd, *cmds, i);
	}
}

void	parent_process(int p_fd[2], int fd[2], t_cmd ***cmds)
{
	close(p_fd[1]);
	if (dup2(p_fd[0], 0) == -1)
		close_all(p_fd, fd, *cmds);
	close(p_fd[0]);
}

pid_t	last_process(int p_fd[2], int fd[2], int argc, t_cmd ***cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		close_all(p_fd, fd, *cmds);
	if (pid == 0)
	{
		if (fd[1] == -1)
		{
			close(p_fd[0]);
			close(p_fd[1]);
			free_for_all(*cmds);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(fd[1], 1);
			close(fd[1]);
			ft_exec(p_fd, fd, *cmds, argc - 1);
		}
	}
	else
		close(0);
	return (pid);
}
