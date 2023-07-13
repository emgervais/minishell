/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egervais <egervais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:18:18 by egervais          #+#    #+#             */
/*   Updated: 2023/07/13 19:34:29 by egervais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int args_count(char *command)// too big
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(*command != '|')
    {
        if(*command == '\"' || *command == '\'')
        {
            i = 1;
            while(command[i] && command[i] != '\"' && command[i] != '\'')//put this check into a function that returns index if positive and 0 if negative
                i++;
            if(!command[i])
                return (0);
            else
            {
                command = &command[i + 1];
                count++;
            }
        }
        while(*command != ' ' && *command != '|' && *command)
            command++;
        while(*command && command[1] == ' ')
            command++;
        command++;
        if(*command != '|')
            count++;
    }
    return (count);
}
int ft_llen(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if(str[i] == '\'' || str[i] == '\"')
    {
        i++;
        count++;
    }
    if(!count)
    {
        while(str[i] && str[i] != ' ')
        {
            i++;
            count++;
        }
    }
    else
    {
        while(str[i] != '\'' && str[i] != '\"')
        {
            i++;
            count++;
        }
    }
    return (count);
}
int fill_point(char *command, char **temp)
{
    char *line;
    int l;
    int i;
    int total_len;

    total_len = 0;
    i = 0;
    while(*command && *command != '|')
    {
        l = ft_llen(command);
        total_len += l;//fuck with quotes
        line = malloc(sizeof(char) * (l + 1));
        line[l] = '\0';
        l = 0;
        while(*command && *command != '|' && *command != ' ')
        {
            line[l++] = *command;
            command++;
        }
        if(*command && *command != '|')
            command++;
        temp[i++] = line;
    }
}
int fill_tokens(char *input, char ***commands)
{
    int i;
    int k;
    int l;
    char **temp;

    i = 0;
    k = 0;
    l = 0;
    while(*input)
    {
        //if(*input == '<' || *input == '>')
        //    input = input/unput(input); //for input and output
        while(*input == ' ')
            input++;
        if(*input == '|')//maybe prob with pipe at the beginning
        {
            input++;
            k++;
        }
        while(*input == ' ')
            input++;
        i = args_count(input);
        temp = malloc(sizeof(char *) * (i + 1));
        temp[i] = NULL;
        i = fill_point(input, temp);
        input += i;
        commands[k] = temp;
        printf("%s\n", temp[l++]);
    }
}
int count_commands(char *line)
{
    int i;
    int count;

    count = 1;
    i = -1;
    while(line[++i])
        if(line[i] == '|')
            count++;
    return (count);
}
char ***get_tokens(char *input)
{
    int count;
    char ***commands;

    count = count_commands(input);
    commands = malloc(sizeof(char **) * (count + 1));
    commands[count] = NULL;
    fill_tokens(input, commands);
}
void lsh_loop(void)
{
    char *input;
    char ***tokens;
    input = readline("minishell : ");
    tokens = get_tokens(input);
    //printf("%s\n", input);
    free(input);
}

int main()
{
    lsh_loop();
}