/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:21:16 by humontas          #+#    #+#             */
/*   Updated: 2025/04/09 17:18:11 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	quote_checker(char *str)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
			double_quote++;
		else if (str[i] == '\'')
			single_quote++;
		i++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
	{
		ft_printf_fd("minishell: unexpected EOF while looking for matching `\"'.\n", 2);
		return (1);
	}
	return (0);
}

static int	parenthesis_checker(char *str)
{
	int	i;
	int	first_parenthesis;
	int	second_parenthesis;

	i = 0;
	first_parenthesis = 0;
	second_parenthesis = 0;
	while (str && str[i])
	{
		if (str[i] == '(')
			first_parenthesis++;
		else if (str[i] == ')')
			second_parenthesis++;
		i++;
	}
	if (first_parenthesis != second_parenthesis)
	{
		ft_printf_fd("minishell: unexpected EOF while looking for matching `('.\n", 2);
		return (1);
	}
	return (0);
}

int	print_syntax_error(int error, char *type)
{
	if (error == 1)
		ft_printf_fd(ERR_TOKEN, 2, type);
	else if (error == 2)
		ft_printf_fd(ERR_SYNTAX, 2);
	return (1);
}

int	check_syntax_error(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == PIPE && (!curr->next || curr->next->type == PIPE))
			return (print_syntax_error(1, "||"));
		if (curr->type == IN || curr->type == OUT || curr->type == APPEND || curr->type == HEREDOC)
		{
			if (!curr->next)
				return (print_syntax_error(2, NULL));
			if (curr->next->type != REDIR)
				return (print_syntax_error(1, curr->next->str));
		}
		curr = curr->next;
	}
	return (0);
}

int	init_parsing(char *str, t_token *tokens)
{
	if (quote_checker(str))
		return (1);
	if (parenthesis_checker(str))
		return (1);
	if (check_syntax_error(tokens))
		return (1);
	return (0);
}
