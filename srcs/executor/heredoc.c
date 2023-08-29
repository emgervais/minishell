/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:04:32 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/29 05:20:27 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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