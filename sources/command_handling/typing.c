/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:18:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 13:27:36 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_redir(t_token **tokens, t_redir **redir)
{
	t_redir	*new;

	new = NULL;
	if ((*tokens) && (*tokens)->next)
	{
		new = new_redir((*tokens)->next->str, (*tokens)->type);
		if (!new)
		{
			redir_clear(redir);
			return (1);
		}
		redir_add_back(redir, new);
		if ((*tokens)->next)
			*tokens = (*tokens)->next->next;
	}
	return (0);
}

int	add_in(t_cmd **cmd, t_token **current)
{
	if (current && *current
		&& ((*current)->type == HEREDOC || (*current)->type == IN))
	{
		if (add_redir(current, &(*cmd)->redir_in))
		{
			cmd_clear(cmd);
			return (1);
		}
	}
	return (0);
}

int	add_out(t_cmd **cmd, t_token **current)
{
	if (current && *current
		&& ((*current)->type == APPEND || (*current)->type == OUT))
	{
		if (add_redir(current, &(*cmd)->redir_out))
		{
			cmd_clear(cmd);
			return (1);
		}
	}
	return (0);
}

int	add_cmd(t_cmd **cmd, t_data *data)
{
	if ((*cmd)->flags && (*cmd)->flags[0])
	{
		(*cmd)->cmd = path_of((*cmd)->flags[0], data->envp);
		if (!(*cmd)->cmd)
		{
			free_tab((*cmd)->flags);
			redir_clear(&(*cmd)->redir_in);
			redir_clear(&(*cmd)->redir_out);
			return (1);
		}
	}
	return (0);
}
