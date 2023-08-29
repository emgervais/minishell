/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:09:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/29 13:34:14 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *lsh_read_line(void)
{
    char    *line;

    line = readline("\033[1;36mminishell\033[34m$ \033[0m");
    
    if (!line)
    {
        if (rl_end > 0)
            write(2, "exit\n", 6);
        if (isatty(STDIN_FILENO))
            write(2, "exit\n", 6);
        free_all(minishell());
        exit(0);//not one?
    }
    add_history(line);
    return (line);
}

static char **lsh_split_line(char *line)
{
    char    **agrs;

    line = ft_strtrim(line, " ");
    agrs = lexer(line);
    free(line);
    if (!agrs)
        return (NULL);
    return (agrs);
}

static void  lsh_execute(char **args, t_env_var *env_var, t_cmds *cmds)
{
    if (!args)
        return ;
    if(parser(args, &cmds))
    {
        free_commands(cmds);
        return ;
    }
    minishell()->cmds = cmds;
    if(executor(cmds, env_var))
    {
        if (cmds->e_status != 0)
            minishell()->status = cmds->e_status;
        free_commands(cmds);
        return ;
    }
    cmds->e_status = 0;
    minishell()->status = 0;
    free_commands(cmds);
}

int    lsh_loop(char **envp)
{
    t_minishell *mini;
    char        *line;
    
    mini = minishell();
    if(!mini)
        exit(1);
    minishell()->env_var = init_env_var(envp);
    if(!minishell()->env_var)
        return(1);
    minishell()->cmds = NULL;
    minishell()->status = 0;
    while (1)
    {
        line = lsh_read_line();
        lsh_execute(lsh_split_line(line), minishell()->env_var, minishell()->cmds);
        minishell()->cmds = NULL;
    }
    free_env_vars(minishell()->env_var);
    return (0);
}
