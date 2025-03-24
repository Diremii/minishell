/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:10:28 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 13:28:23 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (lst[0] == NULL)
		ft_lstadd_front(lst, new);
	else if (lst[0]->next != NULL)
		ft_lstadd_back(&lst[0]->next, new);
	else
	{
		new->previous = lst[0];
		lst[0]->next = new;
	}
}
