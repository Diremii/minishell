/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:58:55 by ttremel           #+#    #+#             */
/*   Updated: 2025/03/24 13:27:10 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*duplst;
	t_list	*dup;
	char	*str;

	dup = NULL;
	duplst = NULL;
	if (!lst || !f || !del)
		return (duplst);
	while (lst != NULL)
	{
		str = (char *)f(lst->content);
		dup = ft_lstnew(str);
		if (!dup)
		{
			ft_lstclear(&duplst, del);
			del(str);
			return (NULL);
		}
		ft_lstadd_back(&duplst, dup);
		lst = lst->next;
	}
	return (duplst);
}
