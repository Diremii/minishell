/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:28:42 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 17:00:47 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_cmd **cmd, t_data *data, int p_fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (redir_in(cmd))
		exit(1);
	close(p_fd[0]);
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close_fd(p_fd);
		exit(1);
	}
	close(p_fd[1]);
	if (redir_out(cmd))
		exit(1);
	clear_history_data(data);
	ft_execve((*cmd), data, p_fd);
	cmd_clear(&data->cmd);
	free_tab(data->envp);
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

static int	do_pipe(t_cmd **cmd, t_data *data)
{
	int		p_fd[2];

	g_signal_pid = 1;
	if (pipe(p_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	data->last_pid = fork();
	if (data->last_pid < 0)
		return (1);
	if (data->last_pid == 0)
		child_process(cmd, data, p_fd);
	else
		parent_process(cmd, p_fd);
	g_signal_pid = 0;
	return (0);
}

static int	last_process(t_cmd **cmd, t_data *data)
{
	if (data->cmd->cmd && (ft_strcmp(data->cmd->flags[0], "cd\0") == 0
			|| ft_strcmp(data->cmd->flags[0], "export\0") == 0))
		return (ft_execve(data->cmd, data, NULL), 0);
	execute_fork(*cmd, data);
	close(0);
	wait_all_pid(data);
	g_signal_pid = 0;
	return (0);
}

int	multi_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	check_all_access(cmd);
	if (cmdsize(data->cmd) <= 1)
	{
		single_process(data);
		dup2(STDOUT_FILENO, 0);
		dup2(STDIN_FILENO, 1);
		return (0);
	}
	while (cmd->next)
	{
		do_pipe(&cmd, data);
		cmd = cmd->next;
	}
	last_process(&cmd, data);
	dup2(STDOUT_FILENO, 0);
	dup2(STDIN_FILENO, 1);
	return (0);
}
