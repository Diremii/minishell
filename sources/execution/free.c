/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:21:08 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/03 14:37:29 by ttremel          ###   ########.fr       */
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

void	close_all(int p_fd[2], int fd[2], t_cmd **cmds)
{
	close_fd(p_fd);
	close_n_exit(fd, cmds);
}
