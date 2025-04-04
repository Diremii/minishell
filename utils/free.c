/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:02:41 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/04 17:14:17 by ttremel          ###   ########.fr       */
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
		free_all(to_free->flags);
		free(to_free);
	}
	*lst = NULL;
}

void	clear_tokens(t_token **tokens)
{
	t_token	*to_free;

	if (!tokens)
		return ;
	while (*tokens != NULL)
	{
		to_free = *tokens;
		*tokens = (*tokens)->next;
		free(to_free->str);
		free(to_free);
	}
	*tokens = NULL;
}
