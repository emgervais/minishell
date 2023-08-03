/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 05:34:41 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 20:08:35 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print commands with different colors
void	print_commands(t_cmds *commands)
{
    t_cmds	*tmp;
    int		i;

    printf("-------------------- Commands --------------------\n");
    tmp = commands;
    while (tmp)
    {
        i = 0;
        printf("\033[1;35m");
        if (tmp->builtin == ECHO)
            printf("echo ");
        else if (tmp->builtin == CD)
            printf("cd ");
        else if (tmp->builtin == PWD)
            printf("pwd ");
        else if (tmp->builtin == EXPORT)
            printf("export ");
        else if (tmp->builtin == UNSET)
            printf("unset ");
        else if (tmp->builtin == ENV)
            printf("env ");
        else if (tmp->builtin == EXIT)
            printf("exit ");
        printf("\033[1;36m");
        while (tmp->args && tmp->args[i])
        {
            printf("%s ", tmp->args[i]);
            i++;
        }
        if (tmp->redir)
        {
            printf("\033[1;33m");
            while (tmp->redir)
            {
                if (tmp->redir->type == OUT)
                    printf(">");
                else if (tmp->redir->type == APPEND)
                    printf(">>");
                else if (tmp->redir->type == IN)
                    printf("<");
                else if (tmp->redir->type == HEREDOC)
                    printf("<<");
                printf(" %s ", tmp->redir->file);
                tmp->redir = tmp->redir->next;
            }
        }
        if (tmp->next)
            printf("\033[0m| ");
        else
            printf("\033[0m\n\n\n");
        tmp = tmp->next;
    }
}

// print key and value with different colors
void    print_env_var(t_env_var *env_var)
{
    t_env_var   *tmp;

    printf("-------------------- Envirronement variables --------------------\n");
    tmp = env_var;
    while (tmp)
    {
        printf("\033[1;36m%s\033[0m=\033[1;32m%s\033[0m\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}