/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:48:35 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/21 14:57:38 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// static void	print_str(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("str[%d]: %s\n", i, str[i]);
// 		i++;
// 	}
// }

t_cmds	*parser(char **str)
{
	t_cmds		*commands;
	t_env_var	*env_var;

	env_var = NULL;
	if (init_env_var_list(str, &env_var))
	{
		printf("no var\n");
		return (NULL);
	}
	check_double_quotes(str);
	if (replace_env_vars(str, env_var))
	{
		printf("no str\n");
		return (NULL);
	}
	// print_str(str);
	commands = init_commands(str);
	if (!commands)
		return (NULL);
	print_args(commands);
	//print_env_var(env_var);
	free_all(commands, env_var, str);
	return (NULL);
}