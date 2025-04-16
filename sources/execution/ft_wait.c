/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:45:26 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/16 14:13:14 by humontas         ###   ########.fr       */
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

	status = 0;
	exit_status = 0;
	waitpid(g_signal_pid, &status, 0);
	if (g_signal_pid == -1)
		return (0);
	waitpid(g_signal_pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (status == SIGQUIT)
			printf("Quit\n");
		else if (status == SIGINT)
			printf("\n");
		exit_status = WTERMSIG(status) + 128;
	}
	return (exit_status);
}
