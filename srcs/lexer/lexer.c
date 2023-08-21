/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:55:45 by ele-sage          #+#    #+#             */
/*   Updated: 2023/08/21 19:01:13 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    }
    if(!c)
    {
        while(str[i] == '|' || str[i] == '<' || str[i] == '>')
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

    in = ft_strtrim(in, " ");
    count = 0;
    if(count == -1)
        return (0);
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
            if(!*in || is_sep(*in))
                count++;
        }
        else if(is_sep(*in))
        {
            if(!valid_sep(in))
                return (syntax_error(*in));
            while(*in && *in == ' ')
                in++;
            if(is_sep(*in))
                count++;
            while(*in && is_sep(*in))
                in++;
        }
        else
        {
            while(*in && !is_sep(*in) && *in != '\'' && *in != '\"')
                in++;
            if(is_sep(*in) || !*in)
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

    if(!input)
        return (NULL);
    k = 0;
    len = count_args(input);
    if(!len)
        return (NULL);
    a = malloc(sizeof(char *) * (len + 1));
    if(!a)
        return (NULL);
    while(*input)
    {
        i = 0;
        while(*input && *input == ' ')
            input++;
        len = llen(input);
        line = malloc(sizeof(char) * (len + 1));
        if(!line)
            return (NULL);
        line[len] = '\0';
        while(i < len)
        {
            line[i++] = *input;
            input++;
        }
        a[k++] = line;
    }
    a[k] = NULL;
    return (a);
}