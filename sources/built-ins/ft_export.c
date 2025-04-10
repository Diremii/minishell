/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttremel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:23:05 by humontas          #+#    #+#             */
/*   Updated: 2025/04/10 17:17:27 by ttremel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char    **add_str_to_tab(char **envp, const char *new_var)
{
    int        i;
    char    **new_envp;

    i = 0;
    while (envp && envp[i])
        i++;
    new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (envp && envp[i])
    {
        new_envp[i] = envp[i];
        i++;
    }
    new_envp[i] = ft_strdup((char *)new_var);
    new_envp[i + 1] = NULL;
    free(envp);
    return (new_envp);
}

static void    print_envp(char **envp)
{
    int    i;

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "_=", 2))
            printf("%s\n", envp[i]);
        i++;
    }
}

static void sort_envp(char **envp)
{
    char *tmp;
    int i = 0;
    int j;

    while (envp[i])
    {
        j = 0;
        while (envp[j] && envp[j + 1])
        {
            if (ft_strcmp(envp[j], envp[j + 1]) > 0)
            {
                tmp = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

static void    set_env_var(t_data *data, const char *new_var)
{
    int        i;
    size_t    len;
    char    *sign;

    sign = ft_strchr(new_var, '=');
    if (!sign)
        return ;
    len = sign - new_var;
    i = 0;
    while (data->envp[i])
    {
        if (!ft_strncmp(data->envp[i], new_var, len) &&
            data->envp[i][len] == '=')
        {
            free(data->envp[i]);
            data->envp[i] = ft_strdup((char *)new_var);
            return ;
        }
        i++;
    }
    data->envp = add_str_to_tab(data->envp, new_var);
}

void    ft_export(t_data *data, char **args)
{
    if (size_of_list(args) == 2)
        set_env_var(data, args[1]);
    sort_envp(data->envp);
    print_envp(data->envp);
}
