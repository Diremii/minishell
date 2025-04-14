/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:29 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 15:21:44 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_unset(t_data *data, char **args)
{
	int i;
	int j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (data->envp[j])
		{
			if (!ft_strncmp(args[i], data->envp[j], ft_strlen(args[i])) && data->envp[j][ft_strlen(args[i])] == '=')
			{
				free(data->envp[j]);
				while (data->envp[j])
				{
					data->envp[j] = data->envp[j + 1];
					j++;
				}
				break;
			}
			j++;
		}
		i++;
	}
}
