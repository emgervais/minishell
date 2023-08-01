/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:16:55 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/01 15:34:35 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		executor(t_cmds *cmds, t_env_var *env_var)
{
    t_cmds	*tmp;
    int		ret;

    tmp = cmds;
    while (tmp)
    {
        tmp->args = expand_args(tmp->args, env_var);
        
        //ret = exec_cmds(tmp, env_var);
        if (ret == ERROR)
            return (ERROR);
        tmp = tmp->next;
    }
    return (ERROR);
}