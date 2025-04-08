/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:23:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/08 15:14:51 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

static void sort_envp(char **envp)
{
	char *tmp;
	int i = 0;
	int j;

	while (envp[i])
	{
		j = 0;
		while (envp[j] && envp[j + 1])
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_export(t_data *data, char **args)
{
	int	i;
	
	i = 0;
	while (args[i])
		i++;
	sort_envp(data->envp);
	if (i == 1)
		print_envp(data->envp);
}
