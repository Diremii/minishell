/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:05:05 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 16:13:39 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_sign(char c)
{
	return ((c == '-' || c == '+'));
}

static int	is_valid(char *num)
{
	ssize_t	i;
	ssize_t	n_zero;
	int		isnum;

	i = -1;
	n_zero = 0;
	isnum = 0;
	while (num[++i])
	{
		if (!ft_isdigit(num[i]))
		{
			if (!num[i + 1] || !is_sign(num[i])
				|| is_sign(num[i + 1]) || i++ != 0)
				return (0);
		}
		if (num[i] == '0' && !isnum)
		{
			n_zero++;
			continue ;
		}
		isnum = 1;
	}
	if (i - n_zero > 20)
		return (0);
	return (1);
}

void ft_exit(t_data *data, char **args)
{
	unsigned char	exit_code;
	__int128_t		very_big;
	int				err;

	exit_code = 0;
	if (!data->cmd->prev && !data->cmd->next)
		ft_printf_fd("exit\n", 1);
	if (size_of_list(args) == 1)
		exit(0);
	if (size_of_list(args) > 2)
	{
		ft_printf_fd("%sexit: too many arguments\n", 2, MINISHELL);
		exit(1);
	}
	err = !is_valid(args[1]);
	very_big = ft_ato128(args[1]);
	if (err || very_big > LLONG_MAX || very_big < LLONG_MIN)
	{
		ft_printf_fd("%sexit: %s: numeric argument required\n", 2,
			MINISHELL, args[1]);
		exit(2);
	}
	exit_code = (unsigned char)very_big;
	exit(exit_code);
}
