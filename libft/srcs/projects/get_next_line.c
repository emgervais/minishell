/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:12:38 by ele-sage          #+#    #+#             */
/*   Updated: 2023/03/06 10:16:37 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*gnl_build_stock(char *stock, char *buffer, ssize_t index)
{
	char	*temp;

	temp = NULL;
	if (!stock)
		stock = ft_substr(buffer, 0, index);
	else
	{
		temp = stock;
		stock = ft_strnjoin(stock, buffer, index);
		free (temp);
	}
	return (stock);
}

static char	*gnl_build_line(char *stock, char *line, ssize_t index)
{
	size_t	a;

	a = 0;
	if (index == 0 && !stock[0])
		return (NULL);
	if (ft_int_strchr(stock, '\n') < 0 && index > 0)
		return (NULL);
	if (ft_int_strchr(stock, '\n') < 0 && index == 0)
		a = ft_int_strchr(stock, '\0');
	else
		a = ft_int_strchr(stock, '\n');
	line = ft_substr(stock, 0, a + 1);
	return (line);
}

static char	*gnl_reader(char **stock, char *line, int fd, ssize_t *index)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*temp;
	size_t		a;

	a = 0;
	temp = NULL;
	if (ft_int_strchr(buffer[fd], '\n') < 0)
	{
		*index = read(fd, buffer[fd], BUFFER_SIZE);
		if (*index < 0)
			return (NULL);
		buffer[fd][*index] = '\0';
		temp = buffer[fd];
		*stock = gnl_build_stock(*stock, temp, *index);
	}
	else
	{
		a = ft_int_strchr(buffer[fd], '\n');
		*stock = ft_substr(buffer[fd], a + 1, *index - a + 1);
		buffer[fd][a] = '0';
	}
	line = gnl_build_line(*stock, line, *index);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*stock;
	char	*line;
	ssize_t	index;

	line = NULL;
	index = BUFFER_SIZE;
	stock = NULL;
	while (fd >= 0 && fd < OPEN_MAX && (!line || !line[0]) && index > 0)
	{
		line = gnl_reader(&stock, line, fd, &index);
		if (line)
		{
			free (stock);
			return (line);
		}
	}
	free (stock);
	free (line);
	return (NULL);
}
