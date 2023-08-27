/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:31:34 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/26 22:22:42 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(t_cmds *cmd)
{
    char *cwd;

    cwd = malloc(sizeof(char) * 1025);
    if (!cwd)
        return (ERROR);
    getcwd(cwd, sizeof(char) * 1025);
    if (!cwd)
        return (error_fd(strerror(errno), 1, cmd));
    ft_putendl_fd(cwd, STDOUT_FILENO);
    free(cwd);
    return (SUCCESS);
}