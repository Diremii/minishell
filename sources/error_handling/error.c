/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:07:00 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 12:14:19 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_msg(char *msg, char *error)
{
	if (!error)
	{
		ft_printf_fd(msg, 2, MINISHELL);
		return (1);
	}
	ft_printf_fd(msg, 2, MINISHELL, error);
	return (1);
}
