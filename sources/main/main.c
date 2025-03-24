/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: humontas <humontas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:15:05 by humontas          #+#    #+#             */
/*   Updated: 2025/03/24 16:31:33 by humontas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	main(void)
// {
// 	t_history	*history;
// 	t_minishell	*data;	
// 	char		*input;

// 	data = malloc(sizeof(t_minishell));
// 	if (!data)
// 		exit_error("minishell: Memory allocation failed\n", 1);
// 	history = malloc(sizeof(t_history));
// 	if (!history)
// 		exit_error("minishell: Memory allocation failed\n", 1);
// 	init_history(history);
// 	while (1)
// 	{
// 		input = readline("minishell > ");
// 		if (!input)
// 			break ;
// 		init_parsing(input);
// 		init_token(input);
// 		add_to_history(history, input);
// 		free(input);
// 	}
// 	close(history->fd);
// 	clear_history();
// }

void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    while (current)
    {
        printf("Token: %s, Type: %d\n", current->str, current->type);
        current = current->next;
    }
}

int main(void)
{
    t_history    *history;
    t_minishell  *data;    
    char         *input;
    t_token      *tokens;  // Ajout de la variable pour stocker les tokens

    // Allocation mémoire
    data = malloc(sizeof(t_minishell));
    if (!data)
        exit_error("minishell: Memory allocation failed\n", 1);

    history = malloc(sizeof(t_history));
    if (!history)
        exit_error("minishell: Memory allocation failed\n", 1);

    init_history(history);

    // Boucle principale
    while (1)
    {
        input = readline("minishell > ");
        if (!input)
            break ;
        
        init_parsing(input);  // Tu pourrais l'utiliser plus tard si nécessaire

        // Créer les tokens et afficher
        tokens = init_token(input);
        print_tokens(tokens);  // Affiche les tokens pour vérifier

        add_to_history(history, input);
        free(input);
    }

    close(history->fd);
    clear_history();
}
