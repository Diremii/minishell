/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:17:38 by humontas          #+#    #+#             */
/*   Updated: 2025/04/14 15:52:33 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_empty_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '!' && str[i] != ':')
			return (0);
		i++;
	}
	return (1);
}

static int	check_history_file(t_history *history)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_printf_fd("minishell: Warning: HOME not set\n", 2);
		return (1);
	}
	history->path = ft_strjoin(home, "/.minishell_history");
	if (!history->path)
	{
		ft_printf_fd("minishell: Warning: History path allocation failed\n", 2);
		return (1);
	}
	history->fd = open(history->path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (history->fd == -1)
	{
		ft_printf_fd("minishell: Warning: Failed to open history file\n", 2);
		free(history->path);
		return (1);
	}
	return (0);
}

static void	load_history_file(t_history *history)
{
	char	*line;
	char	*last;

	last = NULL;
	line = get_next_line(history->fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		add_history(line);
		free(last);
		last = line;
		line = get_next_line(history->fd);
	}
	history->last_command = last;
}

void	add_to_history(t_history *history, const char *command)
{
	if (history->last_command \
		&& ft_strcmp(history->last_command, (char *)command) == 0)
		return ;
	if (is_empty_string((char *)command))
		return ;
	add_history(command);
	write(history->fd, command, ft_strlen(command));
	write(history->fd, "\n", 1);
	if (history->last_command)
		free(history->last_command);
	history->last_command = strdup(command);
}

void	init_history(t_history *history)
{
	if (!check_history_file(history))
		load_history_file(history);
}
