/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:23:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/14 12:51:39 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_envp(char **envp)
{
	int	i;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			sub = ft_strndup(envp[i], ft_strlen(envp[i]) - ft_strlen(ft_strchr(envp[i], '=')) + 1);
			if (ft_strncmp(envp[i], "_=", 2))
				printf("%s%s\"%s\"\n", "declare -x ", sub, ft_strchr(envp[i], '=') + 1);
		}
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

static void	sort_envp(char **envp)
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

static void	set_env_var(t_data *data, const char *new_var)
{
	int		 i;
	size_t	len;

	len = ft_strlen(new_var);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], new_var, len) &&
			data->envp[i][len] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = ft_strdup((char *)new_var);
			return ;
		}
		i++;
	}
	data->envp[i] = ft_strdup((char *)new_var);
}

void	ft_export(t_data *data, char **args)
{
	if (size_of_list(args) == 2)
		set_env_var(data, args[1]);
	sort_envp(data->envp);
	if (size_of_list(args) == 1)
		print_envp(data->envp);
}
