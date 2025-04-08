/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:45:26 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/03 14:46:08 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_all_pid(pid_t pid, size_t size)
{
	size_t	i;
	int		status;
	int		exit_status;

	i = 0;
	while (i < size)
	{
		if (pid == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + 126;
		}
		i++;
	}
	exit(exit_status);
}
