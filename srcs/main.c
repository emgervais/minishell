/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:18:18 by egervais          #+#    #+#             */
/*   Updated: 2023/08/31 20:05:58 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*minishell(void)
{
	static t_minishell	*ptr_address;

	if (!ptr_address)
	{
		ptr_address = malloc(sizeof(t_minishell));
		if (!ptr_address)
			return (NULL);
		ptr_address->env_var = NULL;
		ptr_address->cmds = NULL;
	}
	return (ptr_address);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	(void)argc;
	(void)argv;

	init_signals();
	mini = minishell();
	mini->env_var = init_env_var(envp);
	if (!mini->env_var)
		return (1);
	while (1)
		lsh_loop(mini);
	return (0);
}