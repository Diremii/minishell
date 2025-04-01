/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:58:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/01 18:46:06 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec(int p_fd[2], int fd[2], t_data *data, t_cmd **cmd)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (!(*cmd)->cmd_param[0]
		|| execve((*cmd)->cmd_param[0], (*cmd)->cmd_param, NULL) == -1)
	{
		close_fd(p_fd);
		close_fd(fd);
		cmd_clear(&data->cmd);
		exit(EXIT_FAILURE + 126);
	}
}

static pid_t	do_all_pipes(t_data *data, t_cmd **cmd, int p_fd[2], int fd[2])
{
	size_t	i;
	t_cmd	*current;
	pid_t	pid;

	i = 0;
	current = *cmd;
	while (current->next)
	{
		if (pipe(p_fd) == -1)
			close_n_exit(fd, &data->cmd);
		pid = fork();
		if (pid == -1)
			close_all(p_fd, fd, &data->cmd);
		if (pid == 0)
			child_process(p_fd, fd, data, &current);
		else
			parent_process(p_fd, fd, data);
		current = current->next;
	}
	pid = last_process(p_fd, fd, data, &current);
	return (pid);
}

pid_t	pipex(int fd[2], t_data *data, t_cmd **cmd)
{
	int		p_fd[2];
	pid_t	pid;

	if (check_all_access(cmd, data, (*cmd)->here_doc) == -1)
	{
		close_fd(fd);
		exit(EXIT_FAILURE);
	}
	if (fd[0] != -1)
	{
		if (dup2(fd[0], 0) == -1)
			close_n_exit(fd, &data->cmd);
		close(fd[0]);
	}
	pid = do_all_pipes(data, cmd, p_fd, fd);
	close_fd(p_fd);
	return (pid);
}
