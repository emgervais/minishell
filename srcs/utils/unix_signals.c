/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unix_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:34:31 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/23 11:12:53 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
// Document code below

// This function is called when the user presses Ctrl-C
// It will print a new line, and then replace the current line with an empty string
void	sigint_handler(int sig)
{
    (void)sig;
    ft_putstr_fd("\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    minishell()->status = 1;
}

// This function is called when the user presses Ctrl-D
// It will print "exit", and then exit the program
void	sigquit_handler(int sig)
{
    (void)sig;
    free_all(minishell());
    ft_putstr_fd("exit\n", 1);
}

void	init_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}

void	reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
