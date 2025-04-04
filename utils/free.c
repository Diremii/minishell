/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:02:41 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/04 12:19:05 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
		free(list[i++]);
	free(list);
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
		free_all(to_free->cmd_param);
		free(to_free->infile);
		free(to_free->outfile);
		free(to_free->limiter);
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
	close(data->history.fd);
	free(data->history.last_command);
	free(data->history.path);
	clear_history();
}
