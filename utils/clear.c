/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:16:32 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 13:27:36 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_clear(t_redir **lst)
{
	t_redir	*to_free;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		to_free = *lst;
		*lst = lst[0]->next;
		free(to_free->file);
		free(to_free->limiter);
		free(to_free);
	}
	*lst = NULL;
}

void	cmd_clear(t_cmd **lst)
{
	t_cmd	*to_free;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		to_free = *lst;
		*lst = lst[0]->next;
		if (to_free->redir_in)
			redir_clear(&to_free->redir_in);
		if (to_free->redir_out)
			redir_clear(&to_free->redir_out);
		free(to_free->cmd);
		free_tab(to_free->flags);
		free(to_free);
	}
	*lst = NULL;
}

void	clear_tokens(t_token **tokens)
{
	t_token	*to_free;

	if (!*tokens)
		return ;
	while (*tokens)
	{
		to_free = *tokens;
		*tokens = (*tokens)->next;
		free(to_free->str);
		free(to_free);
	}
	*tokens = NULL;
}

void	clear_history_data(t_data *data)
{
	if (data->history.fd > 2)
		close(data->history.fd);
	if (data->history.last_command)
		free(data->history.last_command);
	if (data->history.path)
		free(data->history.path);
	rl_clear_history();
}

void	clear_all(t_data *data, char *input)
{
	clear_tokens(&data->tokens);
	cmd_clear(&data->cmd);
	free(input);
}
