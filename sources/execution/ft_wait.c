/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:45:26 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 14:57:40 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all_pid(t_data *data)
{
	pid_t	pid;

	wait_pid(data);
	pid = 0;
	while (pid >= 0)
		pid = wait(NULL);
}

void	wait_pid(t_data *data)
{
	int	status;
	int	sig;

	status = 0;
	sig = 0;
	if (data->last_pid == -1)
	{
		data->exit_status = 0;
		return ;
	}
	waitpid(data->last_pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			printf("\n");
		else if (sig == SIGQUIT)
			printf("Quit\n");
		data->exit_status = 128 + sig;
	}
}
