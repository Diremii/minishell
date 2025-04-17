/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:58:17 by humontas          #+#    #+#             */
/*   Updated: 2025/04/17 17:04:19 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_oldpwd(t_data *data)
{
	int		i;
	char	*cwd;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
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
	if (!cwd)
		return ;
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

static int	change_directory_to_home(char *home)
{
	if (home == NULL || chdir(home))
	{
		ft_printf_fd(ERR_HOME, 2, MINISHELL);
		return (1);
	}
	return (0);
}

static int	change_directory(char *path)
{
	if (chdir(path))
	{
		ft_printf_fd(ERR_FILE, 2, MINISHELL);
		return (1);
	}
	return (0);
}

void	ft_cd(t_data *data, char **args)
{
	char	*home;

	(void)data;
	home = getenv("HOME");
	if (size_of_list(args) > 2)
	{
		ft_printf_fd(ERR_ARGS, 2, MINISHELL);
		return ;
	}
	update_oldpwd(data);
	if (size_of_list(args) == 1)
	{
		if (change_directory_to_home(home))
			data->exit_status = 1;
	}
	else if (size_of_list(args) == 2)
	{
		if (change_directory(args[1]))
			data->exit_status = 1;
	}
	update_pwd(data);
}
