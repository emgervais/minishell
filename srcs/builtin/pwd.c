/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:31:34 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 12:42:23 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(int ac)
{
    char *cwd;

    if (ac > 1)
    {
        ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
        return (ERROR);
    }
    cwd = malloc(sizeof(char) * 1025);
    if (!cwd)
        return (ERROR);
    getcwd(cwd, sizeof(char) * 1025);
    ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
    return (SUCCESS);
}