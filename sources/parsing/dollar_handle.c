/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/17 17:02:03 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	add_char_to_lst(t_list **head, char *str, size_t *i)
{
	t_list	*new;
	char	*tmp;

	tmp = ft_strndup(str + *i, 1);
	if (!tmp)
	{
		ft_lstclear(head, free);
		return (1);
	}
	new = ft_lstnew(tmp);
	if (!new)
	{
		ft_lstclear(head, free);
		free(tmp);
		return (1);
	}
	ft_lstadd_back(head, new);
	*i += 1;
	return (0);
}

static int	is_not_valid_char(char c)
{
	if (c == ' ' || c == '\"' || c == '\'' || c == '$' || c == ']'
		|| c == '[' || c == '\0')
		return (1);
	return (0);
}

static void	get_all_var(t_list **head, char *str, t_data *data)
{
	t_list	*new;
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if (quote != '\'' && str[i] == '$' && !is_not_valid_char(str[i + 1]))
		{
			new = handle_dollars(str, &i, quote, data);
			if (!new)
				return ((void)ft_lstclear(head, free));
			ft_lstadd_back(head, new);
		}
		else
			if (add_char_to_lst(head, str, &i))
				return ;
	}
}

static char	*lst_to_str(t_list *head)
{
	t_list	*tmp;
	char	*str;
	char	*new_str;

	str = ft_strdup("");
	tmp = head;
	while (tmp)
	{
		new_str = ft_strjoin(str, (char *)tmp->content);
		free(str);
		str = new_str;
		tmp = tmp->next;
	}
	return (new_str);
}

char	*replace_dolar_in_str(char *str, t_data *data)
{
	t_list	*head;
	char	*new_str;

	if (!str || is_empty_string(str))
		return (NULL);
	head = NULL;
	get_all_var(&head, str, data);
	new_str = lst_to_str(head);
	ft_lstclear(&head, free);
	if (!new_str)
		return (NULL);
	return (new_str);
}
