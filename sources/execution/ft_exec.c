/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:58:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 15:32:19 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	ft_exec(int p_fd[2], int fd[2], t_cmd **cmds, int i)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (!cmds[i]->path
		|| execve(cmds[i]->path, cmds[i]->flags, NULL) == -1)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		close_fd(fd);
		free_for_all(cmds);
		exit(EXIT_FAILURE + 126);
	}
}

static pid_t	do_all_pipes(size_t argc, t_cmd **cmds, int p_fd[2], int fd[2])
{
	size_t	i;
	pid_t	pid;

	i = 0;
	while (i < argc - 1)
	{
		if (pipe(p_fd) == -1)
			close_n_exit(fd, cmds);
		pid = fork();
		if (pid == -1)
			close_all(p_fd, fd, cmds);
		if (pid == 0)
			child_process(p_fd, fd, &cmds, i);
		else
			parent_process(p_fd, fd, &cmds);
		i++;
	}
	pid = last_process(p_fd, fd, argc, &cmds);
	return (pid);
}

pid_t	pipex(int argc, t_cmd **cmds, int fd[2], int here_doc)
{
	int		p_fd[2];
	pid_t	pid;

	if (check_all_access(cmds, here_doc) == -1)
	{
		close_fd(fd);
		exit(EXIT_FAILURE);
	}
	if (fd[0] != -1)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	pid = do_all_pipes(argc, cmds, p_fd, fd);
	close(p_fd[0]);
	close(p_fd[1]);
	return (pid);
}
