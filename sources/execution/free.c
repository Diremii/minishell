/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:21:08 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/06 15:01:14 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	free_all(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

void	free_for_all(t_cmd **list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	free(list[0]->in_file);
	free(list[0]->out_file);
	while (list[i])
	{
		while (list[i]->flags[j])
		{
			if (list[i]->flags[j])
				free(list[i]->flags[j]);
			j++;
		}
		j = 0;
		if (list[i]->path)
			free(list[i]->path);
		if (list[i]->flags)
			free(list[i]->flags);
		list[i]->in_file = NULL;
		list[i]->out_file = NULL;
		free(list[i++]);
	}
	free(list);
}

void	close_fd(int fd[2])
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}

void	close_n_exit(int fd[2], t_cmd **cmds)
{
	close_fd(fd);
	free_for_all(cmds);
	exit(EXIT_FAILURE);
}

void	close_all(int p_fd[2], int fd[2], t_cmd **cmds)
{
	close(p_fd[0]);
	close(p_fd[1]);
	close_n_exit(fd, cmds);
}
