/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:15:53 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 13:27:36 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_arg(t_token **tokens, t_cmd **cmd)
{
	size_t	i;

	if ((*tokens) && ((*tokens)->type == ARG || (*tokens)->type == CMD))
	{
		i = size_of_list((*cmd)->flags);
		if (!(*cmd)->flags)
			(*cmd)->flags = (char **)ft_calloc(2, sizeof(char *));
		if (!(*cmd)->flags)
			return (1);
		(*cmd)->flags[i] = ft_strdup((*tokens)->str);
		if (!(*cmd)->flags[i])
		{
			free_tab((*cmd)->flags);
			return (1);
		}
		(*cmd)->flags = expand_alloc((*cmd)->flags, i + 1, i + 2);
		if (!(*cmd)->flags)
			return (1);
		*tokens = (*tokens)->next;
		i++;
	}
	return (0);
}

int	sort_cmd(t_token **current, t_cmd **cmd, t_data *data)
{
	t_redir	*redir;

	while (*current && (*current)->type != PIPE)
	{
		if (add_in(cmd, current))
			return (1);
		if (add_arg(current, cmd))
		{
			free_tab((*cmd)->flags);
			free((*cmd)->cmd);
			redir_clear(&redir);
			return (1);
		}
		if (add_out(cmd, current))
			return (1);
	}
	if (add_cmd(cmd, data))
		return (1);
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
		if (sort_cmd(&current, &cmd, data))
			return (1);
		cmd_add_back(&data->cmd, cmd);
	}
	return (0);
}
