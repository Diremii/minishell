/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/14 17:54:32 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_all_var(t_list **list, t_data *data)
{
	char	*var;
	size_t	i;
	size_t	size;
	t_list	*tmp;

	i = 0;
	tmp = *list;
	var = NULL;
	while (tmp)
	{
		i = 0;
		if (((char *)tmp->content)[0] == '$')
		{
			size = ft_strlen((char *)tmp->content);
			while (data->envp && data->envp[i])
			{
				if (ft_strncmp(((char *)tmp->content), data->envp[i], size - 1) == 0
					&& data->envp[i][size] == '=')
				{
					var = ft_strdup(ft_strchr(data->envp[i], '=') + 1);
					if (!var)
					{
						ft_lstclear(list, free);
						return ;
					}
				}
				i++;
			}
			if (!var)
			{
				var = ft_strdup("");
				if (!var)
				{
					ft_lstclear(list, free);
					return ;
				}
			}
			free(tmp->content);
			tmp->content = var;
		}
		tmp = tmp->next;
	}
}

char	*join_all_str(t_list **list, t_data *data)
{
	t_list	*tmp;
	char	*str;
	char	*tmp_str;

	tmp = NULL;
	get_all_var(list, data);
	tmp = *list;
	str = malloc(1 * sizeof(char));
	if (!str)
	{
		ft_lstclear(list, free);
		return (NULL);
	}
	str[0] = '\0';
	while (tmp)
	{
		tmp_str = str;
		str = ft_strjoin(tmp_str, (char *)tmp->content);
		printf("str = %s\n", str);
		free(tmp_str);
		tmp_str = NULL;
		if (!str)
		{
			ft_lstclear(list, NULL);
			return (NULL);
		}
		tmp = tmp->next;
	}
	ft_lstclear(list, NULL);
	return (str);
}

char	*convert_all_str(t_list **list)
{
	size_t	i;
	t_list	*tmp;
	t_list	*tmp2;
	char	*str;

	tmp = *list;
	while (tmp)
	{
		str = ft_calloc(ft_lstsize((t_list *)tmp->content) + 1, sizeof(char));
		if (!str)
		{
			ft_lstclear(list, NULL);
			return (NULL);
		}
		i = 0;
		tmp2 = (t_list *)tmp->content;
		while (tmp2)
		{
			str[i++] = (char)(intptr_t)tmp2->content;
			tmp2 = tmp2->next;
		}
		str[i] = '\0';
		ft_lstclear(&tmp2, NULL);
		tmp->content = str;
		tmp = tmp->next;
	}
	return (str);
}

char	*replace_dolar_in_str(char *str, t_data *data)
{
	size_t	i;
	t_list	*tmp;
	t_list	*list;
	t_list	*char_list;

	(void)data;
	i = 0;
	list = NULL;
	char_list = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ')
		{
			tmp = ft_lstnew(char_list);
			ft_lstadd_back(&list, tmp);
			char_list = NULL;
			tmp = ft_lstnew((void *)(intptr_t)str[i]);
			ft_lstadd_back(&char_list, tmp);
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\"')
			{
				tmp = ft_lstnew((void *)(intptr_t)str[i]);
				ft_lstadd_back(&char_list, tmp);
				i++;
			}
			tmp = ft_lstnew(char_list);
			ft_lstadd_back(&list, tmp);
			char_list = NULL;
		}
		else
		{
			tmp = ft_lstnew((void *)(intptr_t)str[i]);
			ft_lstadd_back(&char_list, tmp);
			i++;
		}
	}	
	tmp = ft_lstnew(char_list);
	ft_lstadd_back(&list, tmp);
	// tmp = (t_list *)list->content;
	// while (tmp)
	// {
	// 	printf("char : %c\n", (char)(intptr_t)tmp->content);
	// 	tmp = tmp->next;
	// }
	convert_all_str(&list);
	printf("str : %s\n", (char *)list->content);
	str = join_all_str(&list, data);
	printf("full str = %s\n", str);
	return (str);
}
