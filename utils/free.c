/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:02:41 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 13:28:26 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **list)
{
	int	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
		free(list[i++]);
	free(list);
}

void	free_all(t_data *data)
{
	free_tab(data->envp);
	clear_history_data(data);
	free(data);
}