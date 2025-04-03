/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:51:04 by humontas          #+#    #+#             */
/*   Updated: 2025/04/03 14:57:50 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

int	is_opperator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	**expand_alloc(char **list, size_t old_size, size_t new_size)
{
	char	**new_list;

	if (!list)
		return (NULL);
	new_list = (char **)malloc(new_size * sizeof(char *));
	if (!new_list)
		return (NULL);
	ft_bzero(new_list, new_size * sizeof(char *));
	while (old_size--)
		new_list[old_size] = list[old_size];
	free(list);
	return (new_list);
}
