/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:22:56 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/10 19:00:32 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_string(t_list **list, size_t *i, size_t *j, char *str)
{
	char	quote;
	char	*sub;
	t_list	*tmp;

	quote = str[*i];
	(*i)++;
	*j = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	sub = ft_strndup(str + *j, *i - *j);
	if (!sub)
	{
		ft_lstclear(list, free);
		return ;
	}
	tmp = ft_lstnew(sub);
	if (!tmp)
	{
		free(sub);
		ft_lstclear(list, free);
		return ;
	}
	ft_lstadd_back(list, tmp);
}

void	no_quote_str(t_list **list, size_t *i, size_t *j, char *str)
{
	t_list	*tmp;
	char	*sub;

	*j = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		(*i)++;
	sub = ft_strndup(str + *j, *i - *j);
	if (!sub)
	{
		ft_lstclear(list, free);
		return ;
	}
	tmp = ft_lstnew(sub);
	if (!tmp)
	{
		free(sub);
		ft_lstclear(list, free);
		return ;
	}
	ft_lstadd_back(list, tmp);
}

t_list	*split_str(char *str)
{
	size_t	i;
	size_t	j;
	t_list	*list;

	i = 0;
	j = 0;
	list = NULL;
	while (str[i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			get_string(&list, &i, &j, str);
			if (!list)
				return (NULL);
			i++;
		}
		if (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			no_quote_str(&list, &i, &j, str);
			if (!list)
				return (NULL);
		}
	}
	return (list);
}

char	**chain_to_str(t_list *list)
{
	size_t	i;
	char	**strs;

	i = 0;
	strs = (char **)ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	while (list)
	{
		strs[i++] = (char *)list->content;
		list = list->next;
	}
	strs[i] = NULL;
	return (strs);
}

char	*cut_quote(char *str)
{
	t_list	*list;
	char	**strs;
	char	*new_str;

	list = NULL;
	if (!str)
		return (NULL);
	list = split_str(str);
	if (!list)
	{
		free(str);
		return (NULL);
	}
	strs = chain_to_str(list);
	if (!strs)
	{
		free(str);
		ft_lstclear(&list, free);
		return (NULL);
	}
	new_str = ft_join(strs, "", ft_lstsize(list));
	ft_lstclear(&list, free);
	free(strs);
	free(str);
	return (new_str);
}
