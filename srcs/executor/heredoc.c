/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:04:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/08 19:56:31 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_heredoc(t_cmds *cmds)
{
	t_redir	*tmp;

	tmp = cmds->redir;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static char	*expand_heredoc(char *args, t_env_var *env_var)
{
	char	**keys;

	keys = get_keys(args, 0, 0);
	args = expand_arg(args, env_var, keys);
	ft_free_split(keys);
	return (args);
}

// If the user presses Ctrl-C (SIGINT) while the heredoc is being read,
// the heredoc will be terminated
int	handle_heredoc(t_redir *redir, t_minishell *mini)
{
	int		fd[2];
	char	*input;

	mini->heredoc = 1;
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || mini->ctrl_c
			|| !ft_strncmp(input, redir->file, ft_strlen(redir->file) + 1))
			break ;
		input = expand_heredoc(input, minishell()->env_var);
		ft_putendl_fd(input, fd[1]);
		free(input);
	}
	if (input)
		free(input);
	mini->heredoc = 0;
	mini->ctrl_c = 0;
	return (close(fd[1]), fd[0]);
}
