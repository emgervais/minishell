/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:18:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/29 05:13:43 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_minishell *minishell(void)
{
    static t_minishell *ptr_address = NULL;

    if (!ptr_address)
    {
        ptr_address = malloc(sizeof(t_minishell));
        if (!ptr_address)
            return (NULL);
    }
    return (ptr_address);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    init_signals();
    lsh_loop(envp);
    free_all(minishell());
    return (0);
}
