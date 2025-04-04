/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:28:42 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/04 18:41:04 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec(t_data *data)
{
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return (1);
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		return (1);
	if (g_signal_pid == 0)
	{
		if (data->cmd->redir_out)
		{
			ft_printf_fd("fd[1] : %d\n", 2, data->cmd->redir_out->fd);
			dup2(data->cmd->redir_out->fd, STDOUT_FILENO);
			close(data->cmd->redir_out->fd);
		}
		execve(data->cmd->cmd, data->cmd->flags, NULL);
		if (data->cmd->redir_in)
			close(data->cmd->redir_in->fd);
		exit(0);
	}
	else
	{
		if (data->cmd->redir_in)
			close(data->cmd->redir_in->fd);
		waitpid(g_signal_pid, NULL, 0);
		if (data->cmd->redir_out)
			close(data->cmd->redir_out->fd);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	return (g_signal_pid);
}

int	ft_pipe(t_data *data)
{
	ft_exec(data);
	return (0);
}
