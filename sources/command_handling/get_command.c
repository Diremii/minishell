/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:15:53 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/04 18:51:08 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*create_redir(t_token **tokens)
{
	t_redir	*redir;
	t_redir	*new;

	new = NULL;
	redir = NULL;
	while ((*tokens) && (*tokens)->next && (*tokens)->type != ARG && (*tokens)->type != CMD
		&& (*tokens)->type != PIPE)
	{
		new = new_redir((*tokens)->next->str, (*tokens)->type);
		if (!new)
		{
			redir_clear(&redir);
			return (NULL);
		}
		redir_add_back(&redir, new);
		if ((*tokens)->next)
			*tokens = (*tokens)->next->next;
	}
	return (redir);
}

char	**get_list_of_args(t_token **tokens)
{
	char	**args;
	size_t	i;

	args = (char **)ft_calloc(2, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while ((*tokens) && ((*tokens)->type == ARG || (*tokens)->type == CMD))
	{
		args[i] = ft_strdup((*tokens)->str);
		if (!args[i])
		{
			free_all(args);
			return (NULL);
		}
		args = expand_alloc(args, i + 1, i + 2);
		if (!args)
			return (NULL);
		*tokens = (*tokens)->next;
		i++;
	}
	return (args);
}

int	sort_cmd(t_token **current, t_cmd **cmd)
{
	t_redir	*redir;
	
	while (*current && (*current)->type != PIPE)
	{
		if (get_in(cmd, current))
			return (1);
		(*cmd)->cmd = ft_strdup((*current)->str);
		(*cmd)->flags = get_list_of_args(current);
		if (!(*cmd)->flags || !(*cmd)->cmd)
		{
			free_all((*cmd)->flags);
			free((*cmd)->cmd);
			redir_clear(&redir);
			return (1);
		}
		if (get_out(cmd, current))
			return (1);
		if (arg_after_redir(cmd, current))
			return (1);
	}
	if (*current && (*current)->type == PIPE)
		*current = (*current)->next;
	return (0);
}

int	get_command(t_token *tokens, t_data *data)
{
	t_cmd	*cmd;
	t_token	*current;

	current = tokens;
	data->cmd = NULL;
	while (current)
	{
		cmd = new_cmd(NULL);
		if (!cmd)
			return (1);
		if (sort_cmd(&current, &cmd))
			return (1);
		cmd_add_back(&data->cmd, cmd);
	}
	return (0);
}
