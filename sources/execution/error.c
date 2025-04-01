/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:00 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/01 18:49:40 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	access_to_cmd(t_cmd *cmd)
{
	char	*dup;

	dup = ft_strdup(cmd->cmd_param[0]);
	if (!dup)
		return (-1);
	if (access(dup, F_OK | X_OK) == -1)
		error_msg(2, ft_strrchr(cmd->cmd_param[0], '/') + 1);
	free(dup);
	return (0);
}

static int	access_to_file(char *in_file, char *out_file, int here_doc)
{
	char	*dup;

	dup = NULL;
	if (in_file && !here_doc)
	{
		dup = ft_strdup(in_file);
		if (!dup)
			return (-1);
		if (access(dup, F_OK | R_OK) == -1)
			error_msg(3, dup);
	}
	if (out_file)
	{
		dup = ft_strdup(out_file);
		if (!dup)
			return (-1);
		if (access(dup, W_OK) == -1)
			error_msg(4, dup);
	}
	free(dup);
	return (0);
}

int	check_all_access(t_cmd **cmd, t_data *data, int here_doc)
{
	t_cmd	*current;

	current = *cmd;
	if (access_to_file(current->infile, NULL, here_doc) == -1)
	{
		cmd_clear(&data->cmd);
		return (-1);
	}
	while (1)
	{
		if (access_to_cmd(current))
		{
			cmd_clear(&data->cmd);
			return (-1);
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	if (access_to_file(NULL, current->outfile, 0) == -1)
	{
		cmd_clear(&data->cmd);
		return (-1);
	}
	return (0);
}

void	error_handler(int err, char *error)
{
	error_msg(err, error);
	exit(EXIT_FAILURE);
}

void	error_msg(int err, char *error)
{
	if (err == 0)
		ft_printf_fd(
			"pipex : error : there's too few arguments, 4 needed\n", 2);
	else if (err == 1)
		ft_printf_fd(
			"pipex : error : there's too many arguments, 4 needed\n", 2);
	else if (err == 2)
		ft_printf_fd(
			"pipex : error : command \"%s\" doesn't exist\n", 2, error);
	if (err == 3)
		ft_printf_fd(
			"pipex : error : can't access to file : %s\n", 2, error);
	if (err == 4)
		ft_printf_fd(
			"pipex : error : permission denied : %s\n", 2, error);
}
