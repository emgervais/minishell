/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unix_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:34:31 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/05 00:07:11 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <termios.h>

void	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

// This function is called when the user presses Ctrl-\ (SIGQUIT)
// Will do nothing for Ctrl-\ (SIGQUIT)
void	sigquit_handler(int sig)
{
	(void)sig;
	if (minishell()->waiting_child)
		ft_putstr_fd("Quit: 3\n", 2);
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (!minishell()->waiting_child)
	{
		rl_redisplay();
		minishell()->status = 1;
	}
	else
		minishell()->status = 130;
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigquit_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Cannot set SIGQUIT handler");
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Cannot set SIGINT handler");
		exit(EXIT_FAILURE);
	}
}
