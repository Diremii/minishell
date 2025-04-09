/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:58:17 by humontas          #+#    #+#             */
/*   Updated: 2025/04/09 16:46:03 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_data *data, char **args)
{
	char	*home;

	(void)data;
	home = getenv("HOME");
	if (size_of_list(args) > 2)
	{
		ft_printf_fd(ERR_TOO_ARGS, 2);
		return ;
	}
	else if (size_of_list(args) == 1)
	{
		if (home == NULL || chdir(home))
			return ;
	}
	else if (size_of_list(args) == 2)
	{
		if (chdir(args[1]))
		{
			ft_printf_fd(ERR_NO_FILE, 2);
			return ;
		}
	}
}
