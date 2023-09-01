/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:04:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/09/01 18:40:21 by ele-sage         ###   ########.fr       */
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

int	handle_heredoc(t_redir *redir)
{
	int		fd[2];
	char	*input;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_memcmp(input, redir->file, ft_strlen(input) + 1))
		{
			free(input);
			break ;
		}
		input = expand_heredoc(input, minishell()->env_var);
		ft_putendl_fd(input, fd[1]);
		free(input);
	}
	return (close(fd[1]), fd[0]);
}
