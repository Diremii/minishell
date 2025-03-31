/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:15:53 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/31 15:58:12 by ttremel          ###   ########.fr       */
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

void	typing(t_token **current, t_cmd **cmd)
{
	if ((*current)->type == HEREDOC)
	{
		(*cmd)->here_doc = 1;
		if ((*current)->next)
			(*cmd)->limiter = ft_strdup((*current)->next->str);
	}
	if ((*current)->type == IN)
	{
		if ((*current)->next)
			(*cmd)->infile = ft_strdup((*current)->next->str);
	}
	if ((*current)->type == CMD)
		(*cmd)->cmd_param = get_list_of_args(current);
	if (*current && ((*current)->type == OUT || (*current)->type == APPEND))
	{
		if ((*current)->type == APPEND)
			(*cmd)->append = 1;
		if ((*current)->next)
			(*cmd)->outfile = ft_strdup((*current)->next->str);
	}
}

void	set_inout(t_data *data)
{
	t_cmd	*current;
	t_cmd	*rev;
	char	*in;
	char	*out;

	in = NULL;
	out = NULL;
	current = data->cmd;
	while (current)
	{
		if (current->infile)
			in = current->infile;
		current->infile = in;
		current = current->next;
		if (current && !current->next)
			rev = current;
	}
	while (rev)
	{
		if (rev->outfile)
			out = rev->outfile;
		rev->outfile = out;
		rev = rev->prev;
	}
	
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
		while (current && current->type != PIPE)
		{
			typing(&current, &cmd);
			if (current && current->type != PIPE)
				current = current->next;
		}
		if (current && current->type == PIPE)
			current = current->next;
		cmd_add_back(&data->cmd, cmd);
	}
	//set_inout(data);
	return (0);
}
