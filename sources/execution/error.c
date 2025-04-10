/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:00 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 11:18:30 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	access_to_cmd(t_cmd *cmd)
{
	if (access(cmd->cmd, F_OK) == -1)
	{
		if (ft_strcmp(cmd->flags[0], "cd") == 0
			|| ft_strcmp(cmd->flags[0], "export") == 0)
			return (0);
		error_msg(ERR_UNKNOWN, cmd->flags[0]);
		return (1);
	}
	if (access(cmd->cmd, X_OK) == -1)
	{
		error_msg(ERR_ACCESS, cmd->flags[0]);
		return (1);
	}
	return (0);
}

static int	access_to_file(t_cmd *cmd)
{
	t_redir	*current_redir;
	int		ret;

	current_redir = cmd->redir_in;
	ret = 0;
	while (current_redir && !ret)
	{
		if (!current_redir->here_doc)
		{
			if (access(current_redir->file, F_OK) == -1)
				ret = error_msg(ERR_NO_FILE, current_redir->file);
			if (!ret && access(current_redir->file, R_OK) == -1)
				ret = error_msg(ERR_ACCESS, current_redir->file);
		}
		current_redir = current_redir->next;
	}
	current_redir = cmd->redir_out;
	while (current_redir && !ret)
	{
		if (access(current_redir->file, W_OK) == -1)
			ret = error_msg(ERR_ACCESS, current_redir->file);
		current_redir = current_redir->next;
	}
	return (ret);
}

int	check_all_access(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->cmd)
		{
			if (access_to_cmd(current))
			{
				current = current->next;
				continue ;
			}
		}
		access_to_file(current);
		current = current->next;
	}
	return (0);
}

int	error_msg(char *msg, char *error)
{
	if (!error)
	{
		ft_printf_fd(msg, 2);
		return (1);
	}
	ft_printf_fd(msg, 2, error);
	return (1);
}
