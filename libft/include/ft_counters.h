/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counters.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:01:19 by ele-sage          #+#    #+#             */
/*   Updated: 2023/02/13 19:32:22 by ele-sage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COUNTERS_H
# define FT_COUNTERS_H

# include "libft.h"

/*/////////////////////////////////////////////////////////////////////////////
		COUNT FUNCTIONS
*//////////////////////////////////////////////////////////////////////////////

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);

size_t	ft_count_word(const char *str, const char c);
size_t	ft_count_char(long nb);
size_t	ft_splitlen(char **split);
size_t	ft_atoi_check(const char *str, int *negative);
size_t	ft_count_specific_char(char *str, int c);
size_t	ft_ptrlen(void **ptr);

#endif //FT_COUNTERS_H