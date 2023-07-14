/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:18:18 by egervais          #+#    #+#             */
/*   Updated: 2023/07/14 19:36:13 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history

void    lsh_loop(void)
{
    char    *line;
    int     status;

    status = 1;
    while (status)
    {
        line = readline("minishell : ");
        add_history(line);
        char **pars = pre_pars(line);
        parser(pars);
        free(line);
    }
}

int main()
{
    lsh_loop();
    return (0);
}
