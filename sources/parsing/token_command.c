/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:10:39 by humontas          #+#    #+#             */
/*   Updated: 2025/03/31 15:25:14 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_quote(char *input, size_t *i)
{
	if (input[*i] == '\"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\"')
			(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
	}
}

static void	skip_opperator(char *str, size_t *i, bool skip)
{
	ssize_t    size;

	size = ft_strlen(str) - 1;
	while (size > 0 && is_opperator(str[size]) && skip)
	{
		str[size] = '\0';
		(*i)--;
		size--;
	}
}

char	*get_flag(char *input, size_t *i)
{
	size_t	j;
	size_t	size;
	char	*str;
	bool	skip;

	skip = true;
	j = *i;
	while (input[*i] && input[*i] != ' ')
	{
		skip_quote(input, i);
		(*i)++;
	}
	str = ft_strndup(input + j, *i - j);
	if (!str)
		return (NULL);
	size = ft_strlen(str);
	if (size > 0 && (str[size - 1] == '\'' || str[size - 1] == '\"'))
		skip = false;
	str = cut_quote(str);
	if (!str)
		return (NULL);
	size = ft_strlen(str);
	skip_opperator(str, i, skip);
	return (str);
}

void	handle_args(char *input, size_t *i, t_token **tokens)
{
	char	*flag;
	
	flag = NULL;
	while (input[*i] || !is_opperator(input[*i]))
	{
		free(flag);
		while (input[*i] && input[*i] == ' ' && !is_opperator(input[*i]))
			(*i)++;
		if (!input[*i] || is_opperator(input[*i]))
			return ;
		flag = get_flag(input, i);
		if (!flag)
			return ;
		add_token_to_list(tokens, flag, ARG);
	}
}

void	handle_command(char *input, size_t *i, t_token **tokens, t_data **data)
{
	char	*flag;
	char	*path;
	
	flag = get_flag(input, i);
	if (!flag)
		return ;
	path = path_of(flag, (**data).envp);
	if (!path)
	{
		free(flag);
		return ;
	}
	add_token_to_list(tokens, path, CMD);
	free(path);
	free(flag);
	if (!input[*i - 1])
		return ;
	handle_args(input, i, tokens);
}
