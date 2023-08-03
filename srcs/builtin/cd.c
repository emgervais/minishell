/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/02 12:54:37 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void change_var(char *path, t_env_var *var)
{
    t_env_var *temp;

    temp = var;
    while(ft_strncmp(temp->key, "PWD", 4))
        temp = temp->next;
    free(temp->next->value);
    temp->next->value = temp->value;
    temp->value = temp;
}

int cd(char **args, int ac, t_env_var *var)
{
    char *temp;
    char *cwd;
    
    cwd = malloc(sizeof(char) * 1025);
    getcwd(cwd, sizeof(char) * 1025);
    if(args[1][ft_strlen(args[1])] != '/')
        temp = ft_strjoin(cwd, "/");
    else
        temp = cwd;
    temp = ft_strjoin(temp, args[1]);
    if(!temp || ac != 2 || chdir(temp))
    {
        free(temp);
        free(cwd);
        return (1);
    }
    change_var(temp, var);
    free(cwd);
    return (0);
}
