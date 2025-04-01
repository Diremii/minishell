/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:29 by humontas          #+#    #+#             */
/*   Updated: 2025/04/01 14:30:07 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, char **args)
{
	int	i;
	int	j;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		j = 0;
		while (data->envp[j])
		{
			if (!ft_strcmp(args[i], data->envp[j]))
				free(data->envp[j]);
			j++;
		}
		i++;
	}
}
