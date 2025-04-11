/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:51:29 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 11:56:35 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("JE VIENT DE RENTRER DANS LA BOUCLE MDRRR\n");
		if (!ft_strncmp(args[1], data->envp[i], ft_strlen(args[1])) && data-envp[i][ft_strlen(args[1])])
		{
			printf("COUCOU\n");
			free(data->envp[i]);
			data->envp[i] = NULL;
			printf("%s\n", data->envp[i]);
		}
		i++;
	}
}
