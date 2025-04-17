/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:58:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 16:37:52 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exec_built_ins(t_cmd *cmd, t_data *data)
{
	if (ft_strcmp(cmd->flags[0], "cd") == 0)
		ft_cd(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "export") == 0)
		ft_export(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "exit") == 0)
		ft_exit(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "unset") == 0)
		ft_unset(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "echo") == 0)
		ft_echo(cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(cmd->flags[0], "pwd") == 0)
		ft_pwd();
}

static int	is_built_ins(t_cmd *cmd, t_data *data)
{
	static const char	*built_ins[] = {"echo", "cd", "pwd", "export", \
										"unset", "env", "exit", NULL};
	int					res;
	int					i;

	res = 0;
	i = 0;
	while (i < 7 && !res)
	{
		if (ft_strcmp(cmd->flags[0], built_ins[i]) == 0)
			res = 1;
		i++;
	}
	exec_built_ins(cmd, data);
	return (res);
}

void	ft_execve(t_cmd *cmd, t_data *data, int p_fd[2])
{
	if (!cmd || !cmd->flags)
		exit(1);
	if (is_built_ins(cmd, data))
		return ;
	else if (execve(cmd->cmd, cmd->flags, data->envp) == -1)
	{
		if (p_fd)
			close_fd(p_fd);
		free_tab(data->envp);
		clear_all(data, NULL);
		exit(EXIT_FAILURE + 126);
	}
}

int	execute_fork(t_cmd *cmd, t_data *data)
{
	g_signal_pid = 1;
	data->last_pid = fork();
	if (data->last_pid < 0)
		return (1);
	if (data->last_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (redir_in(&cmd))
			exit(1);
		if (redir_out(&cmd))
			exit(1);
		clear_history_data(data);
		ft_execve(cmd, data, NULL);
		free_tab(data->envp);
		exit(0);
	}
	else
	{
		if (cmd->redir_in)
			close_all(&cmd->redir_in);
		if (cmd->redir_out)
			close_all(&cmd->redir_out);
	}
	return (0);
}

int	single_process(t_data *data)
{

	if (data->cmd->cmd && (ft_strcmp(data->cmd->flags[0], "cd\0") == 0
			|| ft_strcmp(data->cmd->flags[0], "export\0") == 0
			|| ft_strcmp(data->cmd->flags[0], "exit\0") == 0
			|| ft_strcmp(data->cmd->flags[0], "echo\0") == 0))
	{
		ft_execve(data->cmd, data, NULL);
		return (0);
	}
	execute_fork(data->cmd, data);
	wait_pid(data);
	g_signal_pid = 0;
	return (0);
}
