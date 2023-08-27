/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:56:47 by egervais          #+#    #+#             */
/*   Updated: 2023/08/26 22:23:20 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


static int	export_no_arg(t_env_var *env_var, t_cmds *cmd)
{
	while(env_var)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_var->key, STDOUT_FILENO);
		if(env_var->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_var->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env_var = env_var->next;
	}
	cmd->e_status = 0;
	return (SUCCESS);
}

static int	export_wrong_usage(t_cmds *cmd, int i)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd->args[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	cmd->e_status = 1;
	return (ERROR);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	if(!i)
		return (0);
	return (1);
}

// set OLDPWD to like this: OLDPWD
static int set_OLDPWD(t_env_var *env_var)
{
	t_env_var	*tmp;
    t_env_var	*new;

	delete_env_var("OLDPWD", env_var);
    tmp = env_var;
    while (tmp->next)
        tmp = tmp->next;
    new = (t_env_var *)malloc(sizeof(t_env_var));
    if (!new)
        return (ERROR);
    new->key = ft_strdup("OLDPWD");
    if (!new->key)
    {
        free(new);
        return (ERROR);
    }
    new->value = NULL;
    new->next = NULL;
	tmp->next = new;
	return (SUCCESS);
}

int export(t_cmds *cmd, t_env_var *env_var)
{
	int	i;

	i = 1;
	set_OLDPWD(env_var);
	if (cmd->argc == 1)
		return (export_no_arg(env_var, cmd));
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
			return (export_wrong_usage(cmd, i));
		if (ft_strchr(cmd->args[i], '='))
		{
			if(set_env_var(ft_substr(cmd->args[i], 0, ft_int_strchr(cmd->args[i], '=')),
				ft_strchr(cmd->args[i], '=') + 1, env_var))
					return(ERROR);
		}
		i++;
	}
	return (SUCCESS);
}