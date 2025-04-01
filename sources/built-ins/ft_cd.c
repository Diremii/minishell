/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:58:17 by humontas          #+#    #+#             */
/*   Updated: 2025/04/01 12:54:25 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_oldpwd(t_data *data)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "OLDPWD=", 7) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin("OLDPWD=", oldpwd);
			if (!data->envp[i])
				return ;
			free(oldpwd);
			return ;
		}
		i++;
	}
	data->envp[i] = ft_strjoin("OLDPWD=", oldpwd);
	if (!data->envp[i])
		return ;
	free(oldpwd);
}

void	update_pwd(t_data *data)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PWD=", 4) == 0)
		{
			free(data->envp[i]);
			data->envp[i] = ft_strjoin("PWD=", pwd);
			if (!data->envp[i])
				return ;
			free(pwd);
			return ;
		}
		i++;
	}
	data->envp[i] = ft_strjoin("PWD=", pwd);
	if (!data->envp[i])
		return ;
	free(pwd);
}

void	ft_cd(t_data *data, char **args)
{
	int		i;
	char	*home;

	i = 0;
	home = getenv("HOME");
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_printf_fd("cd : too many arguments", 2);
		return ;
	}
	if (i == 1 && home)
		chdir(home);
	if (chdir(args[1]) == -1)
	{
		ft_printf_fd("cd : no such file or directory", 2);
		return ;
	}
}
