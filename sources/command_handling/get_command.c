/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:15:53 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/01 14:01:07 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_list_of_args(t_token **tokens)
{
	char	**args;
	size_t	i;

	args = (char **)ft_calloc(2, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while ((*tokens) && (*tokens)->type != PIPE && (*tokens)->type != OUT
		&& (*tokens)->type != APPEND && (*tokens)->type != HEREDOC
		&& (*tokens)->type != IN)
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
	while (*current && (*current)->type != PIPE)
		{
			if (typing_heredoc(current, cmd))
				return (1);
			if (typing_cmd(current, cmd))
				return (1);
			if (*current && (*current)->type != PIPE)
				*current = (*current)->next;
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
	if (set_in(data))
		return (1);
	if (set_out(data))
		return (1);
	return (0);
}
