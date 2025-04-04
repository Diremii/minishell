/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:18:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/04 18:47:03 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_in(t_cmd **cmd, t_token **current)
{
	t_redir	*redir;

	redir = NULL;
	if (*current && (*current)->type != CMD && (*current)->type != ARG
		&& (*current)->type != PIPE)
	{
		redir = create_redir(current);
		if (!redir)
		{
			cmd_clear(cmd);
			return (1);
		}
		(*cmd)->redir_in = redir;
	}
	return (0);
}

int	get_out(t_cmd **cmd, t_token **current)
{
	t_redir	*redir;

	redir = NULL;
	if (current && *current && (*current)->type != CMD && (*current)->type != ARG
		&& (*current)->type != PIPE)
	{
		redir = create_redir(current);
		if (!redir)
		{
			cmd_clear(cmd);
			return (1);
		}
		(*cmd)->redir_out = redir;
	}
	return (0);
}


char	**append_list_to_list(char **list, char **list2)
{
	size_t	i;
	size_t	size;

	if (!list || !list2)
		return (NULL);
	size = size_of_list(list);
	list = expand_alloc(list, size, size + size_of_list(list2) + 1);
	if (!list)
		return (NULL);
	i = 0;
	while (list2[i])
	{
		list[(size - 1) + i] = ft_strdup(list2[i]);
		if (!list[(size - 1) + i])
		{
			free_all(list);
			list = NULL;
			return (NULL);
		}
		i++;
	}
	list[(size - 1) + i] = NULL;
	return (list);
}

int	arg_after_redir(t_cmd **cmd, t_token **current)
{
	char	**new_args;
	
	new_args = NULL;
	if (current && *current && (*current)->type == ARG)
	{
		new_args = get_list_of_args(current);
		if (!new_args)
		{
			cmd_clear(cmd);
			return (1);
		}
		(*cmd)->flags = append_list_to_list((*cmd)->flags, new_args);
		if (!(*cmd)->flags)
		{
			free_all(new_args);
			cmd_clear(cmd);
			return (1);
		}
	}
	return (0);
}
