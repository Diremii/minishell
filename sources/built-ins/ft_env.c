/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:08:26 by humontas          #+#    #+#             */
/*   Updated: 2025/04/09 11:53:12 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	if (!data->envp && !data->envp[i])
		return ;
	while (data->envp[i])
	{
		printf("%s\n", data->envp[i]);
		i++;
	}
}
