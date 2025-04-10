/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:54:27 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 16:39:15 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_syntax_error(int error, char *type, t_data *data)
{
	data->exit_status = 2;
	if (error == 1)
		ft_printf_fd(ERR_TOKEN, 2, MINISHELL, type);
	else if (error == 2)
		ft_printf_fd(ERR_SYNTAX, 2, MINISHELL);
	else if (error == 3)
		ft_printf_fd(ERR_EOF1, 2, MINISHELL);
	else if (error == 4)
		ft_printf_fd(ERR_EOF2, 2, MINISHELL);
	return (1);
}
