/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:29:10 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 14:01:33 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_add_front(t_cmd **lst, t_cmd *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
	if ((*lst)->next)
		(*lst)->next->prev = *lst;
}

t_cmd	*new_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->flags = args;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		cmd_add_front(lst, new);
	else if ((*lst)->next != NULL)
		cmd_add_back(&(*lst)->next, new);
	else
	{
		new->prev = *lst;
		(*lst)->next = new;
	}
}
