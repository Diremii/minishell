/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:20:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/15 18:22:01 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cut_space(char *str)
{
	char	**lst;
	char	*new_str;
	size_t	size;

	lst = ft_split(str, ' ');
	if (!lst)
		return (NULL);
	size = size_of_list(lst);
	new_str = ft_join(lst, " ", size);
	free_all(lst);
	free(str);
	return (new_str);
}
static char	*get_var(char *str, bool del_space, t_data *data)
{
	size_t	i;
	char	*var;

	i = 0;
	if (!str)
		return (NULL);
	if (str[0] == '?')
	{
		var = ft_itoa(data->exit_status);
		return (var);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i++], str, ft_strlen(str)) == 0
			&& data->envp[i - 1][ft_strlen(str)] == '=')
		{
			var = ft_strdup(data->envp[i - 1] + ft_strlen(str) + 1);
			if (del_space)
				var = cut_space(var);
			return (var);
		}
	}
	var = ft_strdup("");
	return (var);
}

static char	*cut_name(char *str)
{
	size_t	i;
	char	*name;

	i = 0;
	if (str[0] == '?')
		return (ft_strdup("?"));
	while (str[i] && str[i] != ' ' && str[i] != '$'
		&& str[i] != '\"' && str[i] != ']')
		i++;
	name = ft_strndup(str, i);
	return (name);
}

t_list	*handle_dollars(char *str, size_t *i, char quote, t_data *data)
{
	t_list	*new;
	char	*tmp;
	char	*var;
	
	(*i)++;
	tmp = cut_name(str + *i);
	(*i) += ft_strlen(tmp);
	if (quote == '\"')
		var = get_var(tmp, false, data);
	else
		var = get_var(tmp, true, data);
	free(tmp);
	if (!var)
		return (NULL);
	new = ft_lstnew(var);
	if (!new)
	{
		free(var);
		return (NULL);
	}
	return (new);
}
