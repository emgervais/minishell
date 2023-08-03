/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 21:10:06 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/02 15:23:43 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    error_fd(char *str, char *err, int ret, int fd)
{
    ft_putstr_fd("minishell: ", fd);
    ft_putstr_fd(str, fd);
    if (err)
    {
        ft_putstr_fd(": ", fd);
        ft_putstr_fd(err, fd);
    }
    ft_putstr_fd("\n", fd);
    return (ret);
}