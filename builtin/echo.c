/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:21:34 by egervais          #+#    #+#             */
/*   Updated: 2023/07/18 19:32:11 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char *echo(char **args)
{
    int i;
    int mode;
    char *temp;
    char *temp2;

    i = 0;
    mode = 0;
    temp = NULL;
    if(ft_strncmp(args[1], "-n", 3) == 0)
    {
        args++;
        mode = 1;
    }
    args++;
    while(args[i])
    {
        if(!temp)
            temp = ft_strdup(args[i++]);
        else
            temp2 = ft_strjoin(temp, args[i++]);
        free(temp);
        if(args[i])
            temp2 = add_one_char(temp2, ' ', 1);
        else if(!mode)
            temp2 = add_one_char(temp2, '\n', 1);
        if(!temp2)
            return (NULL);
        temp = temp2;
    }
    return (temp2);
}
