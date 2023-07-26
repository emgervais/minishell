/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:09:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/26 05:36:03 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *lsh_read_line(void)
{
    char    *line;

    line = readline("\033[1;36mminishell\033[34m$ \033[0m");
    if (!line)
    {
        ft_putstr_fd("exit\n", 1);
        exit(0);
    }
    add_history(line);
    return (ft_strtrim(line, " "));
}

static char **lsh_split_line(char *line)
{
    char    **agrs;

    agrs = lexer(line);
    free(line);
    if (!agrs)
        return (NULL);
    check_double_quotes(agrs);
    return (agrs);
}

static int  lsh_execute(char **args, t_env_var *env_var)
{
    t_cmds      *cmds;
    int         status;

    cmds = parser(args);
    if (!cmds)
        return (ERROR);
    cmds = expander(cmds, env_var);
    if (!cmds)
        return (ERROR);
    status = executor(cmds, env_var);
    print_commands(cmds);
    //print_env_var(env_var);
    free_commands(cmds);
    return (status);
}

void    lsh_loop(char **envp)
{
    t_env_var   *env_var;
    char        *line;
    char        **args;
    int         status;

    status = 1;
    init_signals();
    env_var = init_env_var(envp);
    while (status)
    {
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args, env_var);
    }
    reset_signals();
}