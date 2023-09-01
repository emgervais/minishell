/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:18:18 by egervais          #+#    #+#             */
/*   Updated: 2023/09/01 17:18:47 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *minishell(void)
{
	static t_minishell *ptr_address;

	if (!ptr_address)
	{
		ptr_address = malloc(sizeof(t_minishell));
		if (!ptr_address)
			return (NULL);
		ptr_address->env_var = NULL;
		ptr_address->cmds = NULL;
		ptr_address->status = 0;
	}
	return (ptr_address);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell *mini;

	init_signals();
	mini = minishell();
	if (!mini)
		return (1);
	mini->env_var = init_env_var(envp);
	if (!mini->env_var)
		return (free(mini), 1);
	while (argc && argv)
		lsh_loop(mini);
	return (0);
}