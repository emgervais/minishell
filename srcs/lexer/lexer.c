/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:55:45 by ele-sage          #+#    #+#             */
/*   Updated: 2023/07/26 04:54:14 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// To do:

static int is_sep(char c)
{
    char sep[5] = {'|', ' ', '<', '>', 0};
    int i;

    i = 0;
    while(sep[i])
        if(c == sep[i++])
            return (1);
    return (0);
}

static int llen(char *str)
{
    int i;
    int c;

    i = 0;
    c = 0;
    while(*str && !is_sep(*str))
    {
        if(*str == '\'' || *str == '\"')
        {
            i = 1;
            while(str[i] && str[i] != *str)
                i++;
            if(!str[i])
                return (0);
            str += i;
            c += i;
        }
        str++;
        c++;
        if(*str == '\'' || *str == '\"')
            return (i + 1);
    }
    if(!c)
    {
        while(str[i] == '|' || str[i] == '<' || str[i] == '>')// check len
            i++;
        return (i);
    }
    return (c);
}

static int valid_sep(char *in)
{
    int i;

    i = 0;
    while(*in && *in == ' ')
        in++;
    while(is_sep(in[i]) && in[i] != ' ')
    {
        if(in[i] != *in)
            return (0);
        i++;
        if(((*in == '<' || *in == '>' )&& i > 2) || (*in == '|' && i > 1))
            return (0);
    }
    in += i;
    while(*in && *in == ' ')
        in++;
    if(is_sep(*in))
        return (0);
    return (1);
}

static int count_args(char *in)
{
    int count;
    int i;

    count = 0;
    while(*in && *in == ' ')
        in++;
    while(*in)
    {
        if(*in == '\'' || *in == '\"')
        {
            i = 1;
            while(in[i] && in[i] != *in)
                i++;
            if(!in[i])
                return (0);
            in += i + 1;
            count++;
        }
        else if(is_sep(*in))
        {
            if(!valid_sep(in))
            {
                printf("error\n");
                exit (1);
            }
            while(*in && is_sep(*in) && *in == ' ')
                in++;
            if(*in && *in != ' ' && is_sep(*in))
                count++;
            while(*in && is_sep(*in))
                in++;
        }
        else
        {
            while(*in && !is_sep(*in) && *in != '\'' && *in != '\"')
                in++;
            count++;
        }
    }
    return (count);
}

char **lexer(char *input)
{
    char *line;
    char **a;
    int len;
    int i;
    int k;

    k = 0;
    len = count_args(input);
    if(!len)
        exit(1);
    a = malloc(sizeof(char *) * (len + 1));
    a[len] = NULL;
    while(*input)
    {
        i = 0;
        while(*input == ' ')
            input++;
        len = llen(input);
        line = malloc(sizeof(char) * (len + 1));
        if(!line)
            exit(1);
        line[len] = '\0';
        while(i < len)
        {
            line[i++] = *input;
            input++;
        }
        a[k] = line;
        printf("%d : %s\n", k, a[k++]);
    }
    return (a);
}