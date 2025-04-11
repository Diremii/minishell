/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:29 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 12:17:07 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(args[1], data->envp[i], ft_strlen(args[1])) && data->envp[i][ft_strlen(args[1])])
		{
			free(data->envp[i]);
			data->envp[i] = NULL;
		}
		i++;
	}
}
