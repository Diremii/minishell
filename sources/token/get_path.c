/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:47:12 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/25 17:50:31 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
