/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:34:39 by ttremel           #+#    #+#             */
/*   Updated: 2025/04/14 18:11:45 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var(char *str, t_data *data)
{
	char	*var;
	int		i;

	i = 0;
	if (str[0] == '?')
	{
		var = ft_itoa(data->exit_status);
		return (var);
	}
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], str, ft_strlen(str)) == 0)
		{
			var = ft_strdup(data->envp[i] + ft_strlen(str) + 1);
			return (var);
		}
		i++;
	}
	var = ft_strdup("");
	return (var);
}

char	*cut_name(char *str)
{
	size_t	i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '\"')
		i++;
	name = ft_strndup(str, i);
	return (name);
}

t_list	*get_all_var(char *str, t_data *data)
{
	t_list	*head;
	t_list	*new;
	size_t	i;
	char	*var;

	i = 0;
	head = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i] != ' ')
		{
			i++;
			var = cut_name(str + i);
			i += ft_strlen(var) - 1;
			var = get_var(var, data);
			new = ft_lstnew(var);
			ft_lstadd_back(&head, new);
		}
		else
			i++;
	}
	return (head);
}

char	*replace_dolar_in_str(char *str, t_data *data)
{
	size_t	i;
	t_list	*head;
	char	*new_str;
	char	*var;
	
	while (str[i]) // TODO: get all var and replace them 
	{
		
	}
}
