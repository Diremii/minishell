/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:52:05 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 11:53:22 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_redir
{
	t_token_type	type;
	struct s_redir	*next;
	struct s_redir	*prev;
	char			*file;
	char			*limiter;
	int				fd;
	int				here_doc;
}			t_redir;

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	t_redir			*redir_in;
	t_redir			*redir_out;
	char			*cmd;
	char			**flags;
}	t_cmd;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
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
	int			exit_status;
	char		**envp;
	char		**paths;
	t_token		*tokens;
	t_cmd		*cmd;
	t_history	history;
}	t_data;

#endif