/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 12:09:13 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 15:26:57 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*lsh_read_line(void)
{
	char	*line;

	line = readline("\033[1;36mminishell\033[34m$ \033[0m");
	if (!line)
	{
		if (rl_end > 0)
			write(2, "exit\n", 6);
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		free_all(minishell());
		exit(0);
	}
	add_history(line);
	return (line);
}

static char	**lsh_split_line(char *line)
{
	char	**agrs;

	line = ft_strtrim(line, " ");
	agrs = lexer(line);
	free(line);
	return (agrs);
}

static void	lsh_execute(char **args, t_minishell *mini)
{
	if (!args)
		return ;
	if (parser(args, mini) == SUCCESS)
		executor(mini);
	ft_free_split(args);
	free_commands(mini->cmds);
}

void	lsh_loop(t_minishell *mini)
{
	char *line;
	char **args;

	mini->cmds = NULL;
	line = lsh_read_line();
	args = lsh_split_line(line);
	lsh_execute(args, mini);
}