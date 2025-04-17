/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:45:26 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 12:44:40 by ttremel          ###   ########.fr       */
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
	int		status;

	status = 0;
	if (data->last_pid == -1)
	{
		data->exit_status = 0;
		return ;
	}
	waitpid(data->last_pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 126;
}
