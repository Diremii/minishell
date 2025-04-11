/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:44:23 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/09 17:30:53 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redir_in(t_cmd **cmd)
{
	t_redir	*current;

	current = NULL;
	if ((*cmd)->redir_in)
	{
		current = (*cmd)->redir_in;
		while (current)
		{
			if (current->fd == -1)
			{
				close_all(&current);
				return (1);
			}
			if (dup2(current->fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				close_all(&(*cmd)->redir_out);
				close_all(&current);
				return (1);
			}
			close(current->fd);
			current = current->next;
		}
	}
	return (0);
}

int	redir_out(t_cmd **cmd)
{
	t_redir	*current;

	current = NULL;
	if ((*cmd)->redir_out)
	{
		current = (*cmd)->redir_out;
		while (current)
		{
			if (current->fd == -1)
			{
				close_all(&current);
				return (1);
			}
			if (dup2(current->fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close_all(&current);
				return (1);
			}
			close(current->fd);
			current = current->next;
		}
	}
	return (0);
}
