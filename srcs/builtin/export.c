/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:56:47 by egervais          #+#    #+#             */
/*   Updated: 2023/07/31 18:37:35 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool is_var_valid(char *str)
{
    int i;

    i = 1;
    if(!ft_isalpha(str[0]) && str[0] != '_')
        return (1);
    while(str[i] && str[i] != '=')
    {
        if(!ft_isalnum(str[i]) && str[i] != '_')
            return (1);
        i++;
    }
    if(!str[i])
        return (1);
    return (0);
    
}

bool	is_exist(char *arg, t_env_var *list, int l)
{
	t_env_var *temp;

	temp = list;
	while(temp)
	{
		if(!ft_strncmp(temp->key, arg, l - 1))
		{
			free(temp->key);
			temp->key = ft_strdup(arg + l);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void list_swap(t_env_var *list)
{
	t_env_var *temp;
	t_env_var *temp2;
	t_env_var *temp3;

	temp = list;
	while(temp->next->next->next)
		temp = temp->next;
	temp2 = temp->next;
	temp3 = temp2->next;
	temp->next = temp3;
	temp3->next = temp2;
	temp2->next = NULL;
}

int add_var(char *args, t_env_var *list)
{
	//char *arg[3] = {"export", "var=mahahahahahahah", NULL};
	t_env_var *temp;
	t_env_var *temp2;
	char *key;
	int i;
	int l;

	i = 0;
	l = -1;
	temp2 = list;
    if(is_var_valid(args))
        return (4);
	while(args[i] != '=')
		i++;
	if(is_exist(args, list, i++))
		return(2);
	key = malloc(sizeof(char) * i);
	while(args[++l] != '=')
		key[l] = args[l];
	key[l] = '\0';
	temp = new_env_var(key, args + i);
	free(key);
	while(temp2->next)
		temp2 = temp2->next;
	temp2->next = temp;
	list_swap(list);
    return (0);
}

int export(char **args, t_env_var *list)
{
	int i;

	i = 1;
	while(args[i])
		add_var(args[i++], list);
}