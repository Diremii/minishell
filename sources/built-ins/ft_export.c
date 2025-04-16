/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:23:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/16 16:53:35 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int parse_arg(char *str)
{
	int	i;
	
	i = 0;
	if (!ft_isalpha(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

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
			free(sub);
		}
		else
			printf("declare -x %s\n", envp[i]);
		i++;
	}
}

static void	sort_envp(char **envp)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[j] && envp[j + 1])
		{
			if (ft_strccmp(envp[j], envp[j + 1], '=') > 0)
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
	int		i;
	size_t	len;

	if (ft_strchr(new_var, '='))
		len = ft_strchr(new_var, '=') - new_var;
	else
		len = ft_strlen(new_var);
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], new_var, len))
		{
			if (!ft_strchr((char *)new_var, '=') && ft_strchr(data->envp[i], '='))
				return ;
			free(data->envp[i]);
			data->envp[i] = ft_strdup((char *)new_var);
			return ;
		}
		i++;
	}
	data->envp = expand_alloc(data->envp, i, i + 2);
	if (!data->envp)
		return ;
	data->envp[i] = ft_strdup((char *)new_var);
	data->envp[i + 1] = NULL;
}

void	ft_export(t_data *data, char **args)
{
	if (size_of_list(args) == 2)
	{
		if (parse_arg(args[1]))
		{
			ft_printf_fd(ERR_ID, 2, MINISHELL, args[1]);
			return ;
		}
		set_env_var(data, args[1]);
	}
	sort_envp(data->envp);
	if (size_of_list(args) == 1)
		print_envp(data->envp);
}
