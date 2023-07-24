/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:53:18 by egervais          #+#    #+#             */
/*   Updated: 2023/07/18 18:28:30 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int cd(char **args, int ac)
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
    return (0);
}

char *pwd(int ac)
{
    char *a;

    if(ac != 1)
        return (1);
    a = malloc(sizeof(char) * 1025);
    if(!a)
        return (1);
    getcwd(a, sizeof(char) * 1025);
    return (a);
}

