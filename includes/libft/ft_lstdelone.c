/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:54:56 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 13:27:51 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	t_list	*to_free;

	if (!lst || !del)
		return ;
	to_free = lst;
	lst = lst->next;
	lst->next->previous = NULL;
	del(to_free->content);
	free(to_free);
}
