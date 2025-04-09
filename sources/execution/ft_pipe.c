/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:28:42 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/09 16:46:29 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_cmd **cmd, t_data *data, int p_fd[2])
{
	if (redir_in(cmd))
		exit(1);
	if (redir_out(cmd))
		exit(1);
	close(p_fd[0]);
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close_fd(p_fd);
		exit(1);
	}
	close(p_fd[1]);
	ft_execve((*cmd), data, p_fd);
	cmd_clear(&data->cmd);
	exit(0);
}

static void	parent_process(t_cmd **cmd, int p_fd[2])
{
	close(p_fd[1]);
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close_fd(p_fd);
		exit(1);
	}
	close(p_fd[0]);
	if ((*cmd)->redir_out)
		close_all(&(*cmd)->redir_out);
	if ((*cmd)->redir_in)
		close_all(&(*cmd)->redir_in);
}

static int	exec_pipe(t_cmd **cmd, t_data *data)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		return (1);
	if (g_signal_pid == 0)
		child_process(cmd, data, p_fd);
	else
		parent_process(cmd, p_fd);
	return (0);
}

static int	last_pipe(t_cmd **cmd, t_data *data)
{
	if (ft_strcmp(data->cmd->flags[0], "cd") == 0
		|| ft_strcmp(data->cmd->flags[0], "export") == 0)
		return (ft_execve(data->cmd, data, NULL), 0);
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		return (1);
	if (g_signal_pid == 0)
	{
		if (redir_in(cmd))
			exit(1);
		if (redir_out(cmd))
			exit(1);
		ft_execve((*cmd), data, NULL);
		exit(0);
	}
	else
	{
		if ((*cmd)->redir_out)
			close_all(&(*cmd)->redir_out);
		if ((*cmd)->redir_in)
			close_all(&(*cmd)->redir_in);
		close(0);
		data->exit_status = wait_all_pid();
	}
	return (0);
}

int	ft_pipe(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (cmdsize(data->cmd) == 1)
	{
		single_cmd(data);
		return (0);
	}
	while (cmd->next)
	{
		exec_pipe(&cmd, data);
		cmd = cmd->next;
	}
	last_pipe(&cmd, data);
	dup2(STDOUT_FILENO, 0);
	dup2(STDIN_FILENO, 1);
	return (0);
}
