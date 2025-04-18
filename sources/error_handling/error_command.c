/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:55:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 19:01:41 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_is_dir(char *path)
{
	struct stat	buf;

	buf.st_mode = 0;
	stat(path, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		error_msg(ERR_IS_DIR, path);
		return (1);
	}
	if (ft_strrchr(path, '/') && ft_strrchr(path, '/')[1] == '\0')
	{
		error_msg(ERR_NO_FILE, path);
		return (1);
	}	
	return (0);
}

static int	access_to_cmd(t_cmd *cmd)
{
	if (ft_strcmp(cmd->flags[0], "cd") == 0
		|| ft_strcmp(cmd->flags[0], "export") == 0
		|| ft_strcmp(cmd->flags[0], "exit") == 0
		|| ft_strcmp(cmd->flags[0], "unset") == 0)
		return (0);
	if (cmd->flags[0][0] == '\0')
	{
		error_msg(ERR_UNKNOWN, cmd->flags[0]);
		return (1);
	}
	if (check_is_dir(cmd->flags[0]))
		return (1);
	if (access(cmd->cmd, F_OK) == -1)
	{
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
