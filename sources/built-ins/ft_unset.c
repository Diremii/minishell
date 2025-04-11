/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:29 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 13:02:37 by ttremel          ###   ########.fr       */
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
			data->envp[i] = NULL;
		}
		i++;
	}
}
