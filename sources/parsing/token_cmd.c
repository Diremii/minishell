/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:05:29 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/25 14:19:55 by ttremel          ###   ########.fr       */
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
	return (NULL);
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

int	check_string(char *input, size_t **i, size_t *j)
{
	char	quote;

	if (input[**i] != '\"' && input[**i] != '\'')
		return (0);
	(**i)++;
	quote = '\'';
	if (input[**i - 1] == '\"')
		quote = '\"';
	while (input[**i] && input[**i] != quote)
		(**i)++;
	(*j)++;
	return (1);
}

int	handle_cmd(char *input, size_t *i, t_token **token)
{
	size_t	j;
	char	*cmd;
	char	*sub;
	int		is_string;

	j = *i;
	if (!input || !input[j])
		return (0);
	is_string = check_string(input, &i, &j);
	while (!is_string && input[*i] && input[*i] != ' ')
		*i += 1;
	sub = ft_substr(input, j, *i - j);
	if (!sub)
		return (0);
	cmd = get_path(sub);
	if (input[*i] && (input[(*i) + 1] == '\"' || input[(*i) + 1] == '\''))
		*i += 2;	
	if (cmd)
	{
		add_token_to_list(token, cmd, CMD);
		free(sub);
		return (1);
	}
	add_token_to_list(token, sub, ARG);
	free(cmd);
	free(sub);
	return (0);
}
