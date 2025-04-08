/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:28:42 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/08 15:44:01 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec(t_data *data)
{
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		return (1);
	if (g_signal_pid == 0)
	{
		if (data->cmd->redir_in)
		{
			dup2(data->cmd->redir_in->fd, STDIN_FILENO);
			close(data->cmd->redir_in->fd);
		}
		if (data->cmd->redir_out)
		{
			dup2(data->cmd->redir_out->fd, STDOUT_FILENO);
			close(data->cmd->redir_out->fd);
		}
		execve(data->cmd->cmd, data->cmd->flags, NULL);
		exit(0);
	}
	else
	{
		if (data->cmd->redir_out)
			close(data->cmd->redir_out->fd);
		waitpid(g_signal_pid, NULL, 0);
	}
	return (g_signal_pid);
}

int	ft_pipe(t_data *data)
{
	if (cmdsize(data->cmd) == 1)
	{
		single_cmd(data);
		return (0);
	}
	//ft_exec(data);
	// dup2(STDOUT_FILENO, 0);
	// dup2(STDIN_FILENO, 1);
	return (0);
}
