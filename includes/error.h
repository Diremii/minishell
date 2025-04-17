/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:45:51 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 15:01:39 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "struct.h"

# define MINISHELL "\033[31m[Minishell]\033[0m "
# define ERR_FILE "%sNo such file or directory\n"
# define ERR_ARGS "%sToo many arguments\n"
# define ERR_SYNTAX "%sSyntax error near unexpected token `newline'\n"
# define ERR_TOKEN "%sSyntax error near unexpected token `%s'\n"
# define ERR_UNKNOWN "%s%s: Command not found\n"
# define ERR_ACCESS "%s%s: Permission denied\n"
# define ERR_NO_FILE "%s%s: No such file or directory\n"
# define ERR_EOF1 "%sunexpected EOF while looking for matching `('\n"
# define ERR_EOF2 "%sunexpected EOF while looking for matching `%s'\n"
# define ERR_ID "%s`%s': not a not a valid identifier\n"
# define ERR_HOME "%sHOME no set\n"
# define ERR_IS_DIR "%s%s: is a directory\n"

int		error_msg(char *msg, char *error);
int		check_all_access(t_cmd *cmd);
int		print_syntax_error(int error, char *type, t_data *data);

#endif