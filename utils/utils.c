/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:51:04 by humontas          #+#    #+#             */
/*   Updated: 2025/04/17 13:33:39 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**expand_alloc(char **list, size_t old_size, size_t new_size)
{
	char	**new_list;

	if (!list)
		return (NULL);
	new_list = (char **)malloc(new_size * sizeof(char *));
	if (!new_list)
	{
		free_tab(list);
		list = NULL;
		return (NULL);
	}
	ft_bzero(new_list, new_size * sizeof(char *));
	while (old_size--)
		new_list[old_size] = list[old_size];
	free(list);
	return (new_list);
}

size_t	cmdsize(t_cmd *cmds)
{
	size_t	size;

	size = 0;
	if (!cmds)
		return (0);
	while (cmds != NULL)
	{
		cmds = cmds->next;
		size++;
	}
	return (size);
}

size_t	size_of_list(char **list)
{
	size_t	i;

	i = 0;
	if (!list)
		return (0);
	while (list[i])
		i++;
	return (i);
}
