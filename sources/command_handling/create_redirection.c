/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:56:06 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 11:37:05 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	redir_add_front(t_redir **lst, t_redir *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
	if ((*lst)->next)
		(*lst)->next->prev = *lst;
}

static int	open_fd(char *content, t_token_type type)
{
	if (type == HEREDOC)
	{
		return (here_doc(content));
	}
	else if (type == IN)
	{
		return (open(content, O_RDONLY, 0777));
	}
	else if (type == OUT || type == APPEND)
	{
		if (type == OUT)
			return (open(content, O_WRONLY | O_CREAT | O_TRUNC, 0777));
		else
			return (open(content, O_WRONLY | O_CREAT | O_APPEND, 0777));
	}
	return (-1);
}

t_redir	*new_redir(char *content, t_token_type type)
{
	t_redir	*redir;
	char	*dup;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	dup = ft_strdup(content);
	if (!dup)
		return (free(redir), NULL);
	redir->fd = open_fd(content, type);
	redir->type = type;
	redir->limiter = NULL;
	redir->here_doc = 0;
	redir->file = dup;
	if (type == HEREDOC)
	{
		redir->here_doc = 1;
		redir->limiter = dup;
		redir->file = NULL;
	}
	redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		redir_add_front(lst, new);
	else if ((*lst)->next != NULL)
		redir_add_back(&(*lst)->next, new);
	else
	{
		new->prev = *lst;
		(*lst)->next = new;
	}
}

t_redir	*redirlast(t_redir *lst)
{
	if (lst == NULL)
		return (lst);
	if (lst->next != NULL)
		return (redirlast(lst->next));
	else
		return (lst);
}
