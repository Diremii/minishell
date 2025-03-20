/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:10:48 by humontas          #+#    #+#             */
/*   Updated: 2025/03/20 13:10:24 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include "libft/libft.h"

typedef struct s_history
{
	char	*path;
	char	*last_command;
	int		fd;
}	t_history;

void	init_history(t_history *history);
void	exit_error(char *str, int exit_code);
void	add_to_history(t_history *history, const char *command);


#endif