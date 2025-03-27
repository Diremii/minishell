/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:10:48 by humontas          #+#    #+#             */
/*   Updated: 2025/03/27 14:00:55 by ttremel          ###   ########.fr       */
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

typedef enum e_token_type
{
	IN = 1,
	HEREDOC = 2,
	OUT = 3,
	APPEND = 4,
	PIPE = 5,
	CMD = 6,
	ARG = 7,
	REDIR = 8
}	t_token_type;

typedef struct s_cmd
{
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token 	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_history
{
	char	*path;
	char	*last_command;
	int		fd;
}	t_history;

typedef struct s_data
{
	char	**envp;
	char	**paths;
	t_token	*tokens;
	t_cmd	*cmd;
}	t_data;

/* HISTORY */
void	init_history(t_history *history);
void	add_to_history(t_history *history, const char *command);

/* TOKENS */
t_token	*init_token(char *input, t_data *data);
t_token	*add_token_to_list(t_token **head, char *str, t_token_type type);
char	*path_of(char *cmd, char **env);
char	*cut_quote(char *str);
void	handle_command(char *input, size_t *i, t_token **tokens, t_data **data);
void	handle_operator(char *input, size_t *i, t_token **tokens);
void	redirection_file_handling(char *input , t_token *tokens, size_t *i);

/* PARSING */
int		is_empty_string(char *str);
int		init_parsing(char *str);

/* UTILS */
void	exit_error(char *str, int exit_code);
int		is_opperator(char c);

/* FREE */
void	free_all(char **list);


#endif