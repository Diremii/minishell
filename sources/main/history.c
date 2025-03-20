/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:17:38 by humontas          #+#    #+#             */
/*   Updated: 2025/03/20 14:15:22 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static int	check_history_file(t_history *history)
{
	char	*home; 
	
	home = getenv("HOME");
	if (!home)
		exit_error("minishell:", 1);
	history->path = ft_strjoin(home, "/.minishell_history");
	if (!history->path)
		exit_error("minishell:", 1);
	history->fd = open(history->path, O_APPEND, 0644);
	if (history->fd == -1)
	{
		free(history->path);
		return (0);
	}
	return (1);
}

static	void	load_history_file(t_history *history)
{
	char *line;
	
	line = get_next_line(history->fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(history->fd);
	}
}

void add_to_history(t_history *history, const char *command)
{
	if (history->last_command && ft_strcmp(history->last_command, (char *)command) == 0)
		return ;
	add_history(command);
	write(history->fd, command, ft_strlen(command));
	write(history->fd, "\n", 1);
	free(history->last_command);
	history->last_command = strdup(command);
}

void	init_history(t_history *history)
{
	if (check_history_file(history))
		load_history_file(history);
}