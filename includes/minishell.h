/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:10:48 by humontas          #+#    #+#             */
/*   Updated: 2025/03/24 16:19:11 by humontas         ###   ########.fr       */
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

# define RESET	"\1\033[0m\2"
# define RED		"\1\033[31m\2"
# define GREEN	"\1\033[32m\2"
# define YELLOW	"\1\033[33m\2"
# define BLUE	"\1\033[34m\2"
# define MAGENTA	"\1\033[35m\2"
# define CYAN	"\1\033[36m\2"
# define WHITE	"\1\033[37m\2"

typedef enum e_token_type
{
	INPUT = 1,
	HEREDOC = 2,
	TRUNC = 3,
	APPEND = 4,
	PIPE = 5,
	CMD = 6,
	ARG = 7
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token 	*next;
}	t_token;

typedef struct s_history
{
	char	*path;
	char	*last_command;
	int		fd;
}	t_history;

typedef struct minishell
{
	char	*envp;
}	t_minishell;


/* HISTORY */
void	init_history(t_history *history);
void	add_to_history(t_history *history, const char *command);

/* PARSING */
int		is_empty_string(char *str);
int		init_parsing(char *str);
void	exit_error(char *str, int exit_code);


#endif