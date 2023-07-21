/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:48:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/20 22:30:18 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmds	*init_commands(char **str)
{
	t_cmds	*commands;

	commands = NULL;
	if (parse_commands(str, &commands))
	{
		printf("Error: parse_commands\n");
		free_commands(commands);
		return (NULL);
	}
	return (commands);
}


void	print_args(t_cmds *commands)
{
	t_cmds	*tmp;
	int		i;

	tmp = commands;
	while (tmp)
	{
		printf("\n");
		i = 0;
		while (tmp->args[i])
		{
			printf("arg[%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		while (tmp->redir)
		{
			printf("redir: %d\n", tmp->redir->type);
			printf("file: %s\n", tmp->redir->file);
			tmp->redir = tmp->redir->next;
		}
		tmp = tmp->next;
	}
}

void	print_env_var(t_env_var *env_var)
{
	while (env_var)
	{
		printf("\nkey: %s\n", env_var->key);
		printf("value: %s\n", env_var->value);
		env_var = env_var->next;
	}
}

void	parser(char **str)
{
	t_cmds	*commands;
	t_env_var	*env_var;

	commands = init_commands(str);
	if (!commands)
	{
		printf("Error: init_commands\n");
		return ;
	}
	check_double_quotes(commands);
	env_var = init_env_var_list(str);
	print_args(commands);
	print_env_var(env_var);
	free_all_env_vars(env_var);
	free_commands(commands);
	ft_free_split(str);
}