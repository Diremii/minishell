/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:02:09 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 15:25:49 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	*no_env(char *cmd)
{
	char	*path;
	char	*dup;

	dup = ft_strdup(cmd);
	if (!dup)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (dup);
	path = ft_strjoin("./", dup);
	free(dup);
	return (path);
}

static char	*create_path(char *cmd, char **paths)
{
	size_t	i;
	char	*path;
	char	*tmp_path;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i++], "/");
		path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	return (no_env(cmd));
}

char	*get_path(char *all_path, char *cmd)
{
	char	**paths;
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (no_env(cmd));
	paths = ft_split(all_path, ':');
	if (!paths)
		return (NULL);
	path = create_path(cmd, paths);
	free_all(paths);
	return (path);
}

char	*path_of(char *cmd, char **env)
{
	size_t	i;
	char	*all_path;
	char	*path;

	i = 0;
	path = "PATH=\0";
	all_path = NULL;
	while (env[i] && ft_strncmp(path, env[i], 5))
		i++;
	if (env[i])
	{
		all_path = ft_strdup(&env[i][5]);
		if (!all_path)
			return (NULL);
		path = get_path(all_path, cmd);
		free(all_path);
	}
	else
		path = no_env(cmd);
	return (path);
}

t_cmd	**parser(char **argv, int argc, char *env)
{
	t_cmd	**list_command;
	int		i;

	i = 0;
	list_command = (t_cmd **)malloc((argc + 1) * sizeof(t_cmd *));
	if (!list_command)
		return (NULL);
	ft_bzero(list_command, (argc + 1) * sizeof(t_cmd *));
	while (i < argc)
	{
		list_command[i] = (t_cmd *)malloc(sizeof(t_cmd));
		list_command[i]->in_file = NULL;
		list_command[i]->out_file = NULL;
		list_command[i]->env = env;
		list_command[i]->flags = ft_split(argv[i], ' ');
		list_command[i]->path = path_of(list_command[i]->flags[0], env);
		if (!list_command[i]->flags)
		{
			free_for_all(list_command);
			return (NULL);
		}
		i++;
	}
	list_command[i] = NULL;
	return (list_command);
}
