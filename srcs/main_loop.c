/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:09:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/04 12:47:27 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *lsh_read_line(void)
{
    char    *line;

    line = readline("\033[1;36mminishell\033[34m$ \033[0m");
    if (!line)
    {
        ft_putstr_fd("exit\n", STDOUT_FILENO);
        free_all(minishell());
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

static int  lsh_execute(char **args, t_env_var *env_var, t_cmds *cmds)
{
    int         status;

    status = 0;
    if (!args)
        return (status);
    if (parser(args, &cmds))
        return (ERROR);
    if (!cmds)
        return (status);
    if(executor(cmds, env_var))//add prot
    {
        if (cmds->fd.status != 0)
            status = cmds->fd.status;
        else
            status = 1;
    }
    free_commands(cmds);
    return (status);
}

void    lsh_loop(char **envp)
{
    t_env_var   *env_var;
    t_cmds      *cmds;
    char        *line;
    char        **args;

    init_signals();
    env_var = init_env_var(envp);
    cmds = NULL;
    minishell()->env_var = env_var;
    minishell()->cmds = cmds;
    minishell()->status = 0;
    while (1)
    {
        line = lsh_read_line();
        args = lsh_split_line(line);
        minishell()->status = lsh_execute(args, env_var, cmds);
    }
    free_env_vars(env_var);
    reset_signals();
}