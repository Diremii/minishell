/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:00 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/09 15:24:04 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_handler(int err, char *error)
{
	error_msg(err, error);
	exit(EXIT_FAILURE);
}

void	error_msg(int err, char *error)
{
	if (err == 0)
		ft_printf_fd(
			"minishell : error : there's too few arguments, 4 needed\n", 2);
	else if (err == 1)
		ft_printf_fd(
			"minishell : error : there's too many arguments, 4 needed\n", 2);
	else if (err == 2)
		ft_printf_fd(
			"minishell : error : command \"%s\" doesn't exist\n", 2, error);
	if (err == 3)
		ft_printf_fd(
			"minishell : error : can't access to file : %s\n", 2, error);
	if (err == 4)
		ft_printf_fd(
			"minishell : error : permission denied : %s\n", 2, error);
}
