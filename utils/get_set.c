/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:27:01 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 12:30:20 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_data	*set_data(t_history *history)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->history = *history;
	data->envp = NULL;
	data->exit_status = 0;
	data->last_pid = 0;
	data->cmd = NULL;
	data->tokens = NULL;
	data->paths = NULL;
	return (data);
}

t_data	*get_data(t_history *history)
{
	static t_data	*data = NULL;

	if (!data)
		data = set_data(history);
	return (data);
}
