/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/11 17:54:24 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_chained_list(t_list *list)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (list)
	{
		if (ft_strchr(list->content, '$'))
		{
			list = list->next;
			continue ;
		}
		tmp = str;
		str = ft_strjoin(tmp, list->content);
		free(tmp);
		list = list->next;
	}
	return (str);
}

char	*replace_dolar_in_str(char *str, t_data *data)
{
	size_t	i;
	t_list	*list;

	i = 0;
	(void)data;
	while (1)
	{
		if (str[i] == '\'')
		{
			while (str[i] && str[++i] != '\'')
				;
			list = ft_lstnew(ft_strndup(str, i - 1));
			str = ft_strcat(str, str + i - 1);
		}
		while (str[i] && str[i] != '$' && str[i] != '\'')
			i++;
		list = ft_lstnew(ft_strndup(str, i - 1));
		if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '$')
				i++;
			list = ft_lstnew(ft_strndup(str, i - 1));
			str = ft_strcat(str, str + i - 1);
		}
		if (!str[i])
			break ;
		ft_strcat(str, str + i - 1);
		i = 0;
	}
	free(str);
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
	return (NULL);
}
