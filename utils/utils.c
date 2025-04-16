/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:51:04 by humontas          #+#    #+#             */
/*   Updated: 2025/04/16 17:06:36 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *str, int exit_code)
{
	perror(str);
	exit(exit_code);
}

int	ft_strccmp(char *s1, char *s2, char c)
{
	char	*str1;
	char	*str2;
	size_t			i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	str1 = ft_strndup(s1, strclen(s1, c) - 1);
	str2 = ft_strndup(s2, strclen(s2, c) - 1);
	if (!str1 || !str2)
	{
		free(str1);
		free(str2);
		return (-1);
	}
	while ((str1[i] != '\0' && str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	i = str1[i] - str2[i];
	free(str1);
	free(str2);
	return (i);
}

char	**expand_alloc(char **list, size_t old_size, size_t new_size)
{
	char	**new_list;

	if (!list)
		return (NULL);
	new_list = (char **)malloc(new_size * sizeof(char *));
	if (!new_list)
	{
		free_all(list);
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
