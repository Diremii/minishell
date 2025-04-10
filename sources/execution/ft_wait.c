/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:45:26 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 13:13:48 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_all_pid(void)
{
	pid_t	pid;
	int		exit_status;

	exit_status = wait_pid();
	pid = 0;
	while (pid >= 0)
		pid = wait(NULL);
	return (exit_status);
}

int	wait_pid(void)
{
	int		status;
	int		exit_status;

	exit_status = 0;
	if (g_signal_pid == -1)
		return (0);
	g_signal_pid = waitpid(g_signal_pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = WTERMSIG(status) + 126;
	return (exit_status);
}
