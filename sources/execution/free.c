/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:21:08 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/08 14:50:23 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fd(int fd[2])
{
	if (fd && fd[0] != -1)
		close(fd[0]);
	if (fd && fd[1] != -1)
		close(fd[1]);
}

void	close_n_exit(int fd[2], t_cmd **cmds)
{
	close_fd(fd);
	cmd_clear(cmds);
	exit(EXIT_FAILURE);
}

void	close_all(t_redir **redir)
{
	t_redir	*current;

	current = *redir;
	while (current)
	{
		if (current->fd != -1)
			close(current->fd);
		current = current->next;
	}
}
