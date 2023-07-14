/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projects.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:01:57 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/07 10:43:14 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROJECTS_H
# define FT_PROJECTS_H

# include "libft.h"

/*/////////////////////////////////////////////////////////////////////////////
		PROJECTS FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

//char	*gnl_build_stock(char *stock, char *buffer, ssize_t index);
//char	*gnl_build_line(char *stock, char *line, ssize_t index);
//char	*gnl_reader(char **stock, char *line, int fd, ssize_t *index);
char	*get_next_line(int fd);
//int	ft_print_parse(va_list ap, char fc);
int		ft_printf(const char *format, ...);

char	*ft_gnl_join(int fd);
//int	ft_print_parse_fd(va_list ap, char fc, int fd);
int		ft_dprintf(int fd, const char *format, ...);

#endif //FT_PROJECTS_H