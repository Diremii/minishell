/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:58:17 by humontas          #+#    #+#             */
/*   Updated: 2025/04/11 12:49:36 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_oldpwd(t_data *data)
{
	int		i;
	char	*cwd;
	
	i = 0;
	cwd = getcwd(NULL, 0);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "OLDPWD=", 7))
		{
			data->envp[i] = ft_strjoin("OLDPWD=", cwd);
			free(cwd);
			return ;
		}
		i++;
	}
	free(cwd);
}

static void	update_pwd(t_data *data)
{
	int		i;
	char	*cwd;
	
	i = 0;
	cwd = getcwd(NULL, 0);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], "PWD=", 4))
		{
			data->envp[i] = ft_strjoin("PWD=", cwd);
			free(cwd);
			return ;
		}
		i++;
	}
	free(cwd);
}

void	ft_cd(t_data *data, char **args)
{
	char	*home;

	(void)data;
	home = getenv("HOME");
	if (size_of_list(args) > 2)
	{
		ft_printf_fd(ERR_ARGS, 2);
		return ;
	}
	else if (size_of_list(args) == 1)
	{
		if (home == NULL || chdir(home))
			return ;
	}
	else if (size_of_list(args) == 2)
	{ 
		if (chdir(args[1]))
		{
			ft_printf_fd(ERR_FILE, 2);
			return ;
		}
	}
	update_oldpwd(data);
	update_pwd(data);
}
