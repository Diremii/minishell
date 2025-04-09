/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:58:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/09 15:56:33 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_built_ins(t_cmd *cmd, t_data *data)
{
	static const char	*built_ins[] = {"echo", "cd", "pwd", "export", \
										"unset", "env", NULL};
	int					res;
	int					i;

	res = 0;
	i = 0;
	while (i < 6 && !res)
		if (ft_strcmp(cmd->flags[0], built_ins[i++]) == 0)
			res = 1;
	if (ft_strcmp(cmd->flags[0], "cd") == 0)
		ft_cd(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "export") == 0)
		ft_export(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "unset") == 0)
		ft_unset(data, cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "echo") == 0)
		ft_echo(cmd->flags);
	else if (ft_strcmp(cmd->flags[0], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(cmd->flags[0], "pwd") == 0)
		ft_pwd();
	return (res);
}

void	ft_execve(t_cmd *cmd, t_data *data, int p_fd[2])
{
	if (!cmd || !cmd->flags)
		return ;
	if (is_built_ins(cmd, data))
		return ;
	if (execve(cmd->cmd, cmd->flags, data->envp) == -1)
	{
		if (p_fd)
			close_fd(p_fd);
		exit(EXIT_FAILURE + 126);
	}
}

int	single_cmd(t_data *data)
{

	if (ft_strcmp(data->cmd->flags[0], "cd\0") == 0
		|| ft_strcmp(data->cmd->flags[0], "export\0") == 0)
	{
		ft_execve(data->cmd, data, NULL);
		return (0);
	}
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		return (1);
	if (g_signal_pid == 0)
	{
		if (redir_in(&data->cmd))
		{
			close_all(&data->cmd->redir_out);
			exit(1);
		}
		if (redir_out(&data->cmd))
			exit(1);
		ft_execve(data->cmd, data, NULL);
		exit(0);
	}
	else
	{
		if (data->cmd->redir_in)
			close_all(&data->cmd->redir_in);
		if (data->cmd->redir_out)
			close_all(&data->cmd->redir_out);
		// if (ft_strcmp(data->cmd->flags[0], "cd\0") == 0)
		// {
		// 	ft_execve(data->cmd, data, NULL);
		// }
		waitpid(g_signal_pid, NULL, 0);
	}
	return (g_signal_pid);
}
