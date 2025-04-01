/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:49:16 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/01 13:54:39 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	typing_heredoc(t_token **current, t_cmd **cmd)
{
	if ((*current)->type == HEREDOC)
	{
		(*cmd)->here_doc = 1;
		if ((*current)->next)
		{
			(*cmd)->limiter = ft_strdup((*current)->next->str);
			if (!(*cmd)->limiter)
				return (1);
		}
	}
	if ((*current)->type == IN)
	{
		if ((*current)->next)
		{
			(*cmd)->infile = ft_strdup((*current)->next->str);
			if (!(*cmd)->infile)
				return (1);
		}
	}
	return (0);
}

int	typing_cmd(t_token **current, t_cmd **cmd)
{
	if ((*current)->type == CMD)
	{
		(*cmd)->cmd_param = get_list_of_args(current);
		if (!(*cmd)->cmd_param)
			return (1);
	}
	if (*current && ((*current)->type == OUT || (*current)->type == APPEND))
	{
		if ((*current)->type == APPEND)
			(*cmd)->append = 1;
		if ((*current)->next)
		{
			(*cmd)->outfile = ft_strdup((*current)->next->str);
			if (!(*cmd)->outfile)
				return (1);
		}
	}
	return (0);
}
int	set_in(t_data *data)
{
	t_cmd	*current;
	char	*in;

	in = NULL;
	current = data->cmd;
	while (current)
	{
		if (current->infile)
			in = current->infile;
		current->infile = ft_strdup(in);
		if (!current->infile)
			return (1);
		current = current->next;
	}
	return (0);
}

int	set_out(t_data *data)
{
	t_cmd	*current;
	char	*out;

	out = NULL;
	current = cmdlast(data->cmd);
	while (current)
	{
		if (current->outfile)
			out = current->outfile;
		current->outfile = ft_strdup(out);
		if (!current->outfile)
			return (1);
		current = current->prev;
	}
	return (0);
}
