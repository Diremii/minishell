/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:05:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 19:13:50 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

char	*get_path(char *cmd)
{
	char	**paths;
	char	*all_path;
	char	*path;

	all_path = getenv("PATH");
	if (ft_strchr(cmd, '/'))
		return (no_env(cmd));
	paths = ft_split(all_path, ':');
	if (!paths)
		return (NULL);
	path = create_path(cmd, paths);
	free_all(paths);
	return (path);
}

int	handle_cmd(char *input, size_t *i, t_token **token)
{
	size_t	j;
	char	*cmd;
	char	*sub;

	j = *i;
	if (!input)
		return (0);
	while (input[*i] && input[*i] != '\n' && input[*i] != ' ')
		*i += 1;
	sub = ft_substr(input, j, *i - j);
	if (input[*i])
		*i += 1;
	if (!sub)
		return (0);
	cmd = get_path(sub);
	if (cmd)
	{
		add_token_to_list(token, cmd, CMD);
		free(sub);
		return (1);
	}
	free(sub);
	free(cmd);
	return (0);
}
