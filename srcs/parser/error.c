/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:10:06 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/19 21:11:32 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_redir(t_cmds *commands)
{
    t_cmds	*tmp;

    tmp = commands;
    while (tmp)
    {
        if (tmp->redir_type != NO_REDIR && tmp->redir_file == NULL)
        {
            printf("minishell: syntax error near unexpected token `newline'\n");
            return ;
        }
        tmp = tmp->next;
    }
}