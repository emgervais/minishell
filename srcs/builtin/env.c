/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:32:20 by egervais          #+#    #+#             */
/*   Updated: 2023/09/01 18:43:13 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*add_one_char(char *s1, char c, int malloced)
{
	char	*str;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	if (malloced)
		free(s1);
	return (str);
}

int	env(t_cmds *cmd, t_env_var *env_var)
{
	int	i;

	i = 0;
	while (env_var)
	{
		ft_putstr_fd(env_var->key, cmd->fd.fd_out);
		ft_putstr_fd("=", cmd->fd.fd_out);
		ft_putstr_fd(env_var->value, cmd->fd.fd_out);
		ft_putstr_fd("\n", cmd->fd.fd_out);
		env_var = env_var->next;
	}
	return (SUCCESS);
}
