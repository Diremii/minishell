/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:02:41 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/27 15:52:05 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

void	cmd_clear(t_cmd **lst)
{
	t_cmd	*to_free;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		to_free = *lst;
		*lst = lst[0]->next;
		free_all(to_free->cmd_param);
		free(to_free->infile);
		free(to_free->outfile);
		free(to_free);
	}
	*lst = NULL;
}

