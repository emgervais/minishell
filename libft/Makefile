# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 10:24:39 by ele-sage          #+#    #+#              #
#    Updated: 2023/02/27 19:13:21 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all clean fclean re norm
.SILENT:

NAME		:=	libft.a

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

# Files
LST_INCS			:=	libft.h					ft_booleans.h		\
					ft_conversions.h			ft_counters.h		\
					ft_lists.h					ft_maths.h			\
					ft_memory.h					ft_prints.h			\
					ft_projects.h				ft_strings.h

LST_BOOLEANS		:=	ft_isalnum.c			ft_isalpha.c		\
					ft_isascii.c				ft_ischarset.c		\
					ft_isdigit.c				ft_islower.c		\
					ft_isnotcharset.c			ft_isprime.c		\
					ft_isprint.c				ft_isspace.c		\
					ft_isupper.c

LST_CONVERSIONS	:=	ft_atoi.c					ft_atol.c			\
					ft_big_atoi.c				ft_big_atol.c		\
					ft_itoa.c					ft_str_tolower.c	\
					ft_str_toupper.c			ft_striteri.c		\
					ft_strmapi.c				ft_swap.c			\
					ft_tolower.c				ft_toupper.c		\
					ft_add_str_to_int.c			ft_atof.c			\
					ft_replace_char.c			ft_convert_base.c	\

LST_COUNTERS		:=	ft_count_char.c			ft_count_word.c		\
					ft_strlcat.c				ft_strlcpy.c		\
					ft_strlen.c					ft_splitlen.c		\
					ft_atoi_check.c				ft_count_specific_char.c \
					ft_ptrlen.c

LST_LISTS			:=	ft_lstadd_back.c		ft_lstadd_front.c	\
					ft_lstclear.c				ft_lstdelone.c		\
					ft_lstiter.c				ft_lstlast.c		\
					ft_lstmap.c					ft_lstnew.c			\
					ft_lstsize.c				ft_lstfree.c

LST_MATHS			:=	ft_approx_sqrt.c		ft_factorial.c		\
					ft_find_next_prime.c		ft_get_highest.c	\
					ft_power.c					ft_sqrt.c			\
					ft_get_lowest.c				ft_pourcent.c		\
					ft_abs.c	

LST_MEMORY			:=	ft_bzero.c				ft_calloc.c			\
					ft_free_split.c				ft_free.c			\
					ft_memchr.c					ft_memcmp.c			\
					ft_memcpy.c					ft_memmove.c		\
					ft_memset.c					ft_realloc.c

LST_PRINTS			:=	ft_int_putchar_fd.c		ft_int_putchar.c	\
					ft_int_putnbr_base_fd.c		ft_int_putnbr_base.c\
					ft_int_putnbr_fd.c			ft_int_putnbr.c		\
					ft_int_putptr_fd.c			ft_int_putptr.c		\
					ft_int_putstr_fd.c			ft_int_putstr.c		\
					ft_putchar_fd.c				ft_putendl_fd.c		\
					ft_putnbr_base_fd.c			ft_putnbr_fd.c		\
					ft_putptr_fd.c				ft_putstr_fd.c

LST_PROJECTS		:=	ft_gnl_join.c			ft_printf.c			\
					get_next_line.c				ft_dprintf.c

LST_STRINGS			:=	ft_int_strchr.c			ft_split.c			\
					ft_strcat.c					ft_strchr.c			\
					ft_strcpy.c					ft_strdup.c			\
					ft_strfreejoin.c			ft_strjoin.c		\
					ft_strncat.c				ft_strncmp.c		\
					ft_strncpy.c				ft_strnjoin.c		\
					ft_strnstr.c				ft_strrchr.c		\
					ft_strstr.c					ft_strtrim.c		\
					ft_substr.c					ft_unsplit.c		\
					ft_int_strrchr.c

# Directories
P_INCS			:=	include/
P_SRCS			:=	srcs/
P_BOOLEANS		:=	booleans/
P_CONVERSIONS	:=	conversions/
P_COUNTERS		:=	counters/
P_LISTS			:=	lists/
P_MATHS			:=	maths/
P_MEMORY		:=	memory/
P_PRINTS		:=	prints/
P_PROJECTS		:=	projects/
P_STRINGS		:=	strings/
P_OBJS			:=	.objs/

# Shortcuts
INCS	:=	$(addprefix $(P_INCS),$(LST_INCS))

SRCS	:=	$(addprefix $(P_SRCS)$(P_BOOLEANS),$(LST_BOOLEANS))			\
			$(addprefix $(P_SRCS)$(P_CONVERSIONS),$(LST_CONVERSIONS))	\
			$(addprefix $(P_SRCS)$(P_COUNTERS),$(LST_COUNTERS))			\
			$(addprefix $(P_SRCS)$(P_LISTS),$(LST_LISTS))				\
			$(addprefix $(P_SRCS)$(P_MATHS),$(LST_MATHS))				\
			$(addprefix $(P_SRCS)$(P_MEMORY),$(LST_MEMORY))				\
			$(addprefix $(P_SRCS)$(P_PRINTS),$(LST_PRINTS))				\
			$(addprefix $(P_SRCS)$(P_PROJECTS),$(LST_PROJECTS))			\
			$(addprefix $(P_SRCS)$(P_STRINGS),$(LST_STRINGS))

OBJS	:=	$(subst $(P_SRCS),$(P_OBJS),$(SRCS:.c=.o))

#//////////////////////////////////////////////////////////////////////////////
#		FLAGS & TEXT MODIFIERS
#//////////////////////////////////////////////////////////////////////////////

# Flags
CC			:=	gcc
CF			:=	-Wall -Werror -Wextra
CS			:=	-g -fsanitize=address
CI			:=	-I $(P_INCS)
CG			:=	-g3
AR			:=	ar rcs
RM			:=	rm -rf

# Colors
BLACK=\033[30m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
PURPLE=\033[35m
CYAN=\033[36m
WHITE=\033[37m

# Text
ERASE=\033[2K\r
RESET=\033[0m
BOLD=\033[1m
FAINT=\033[2m
ITALIC=\033[3m
UNDERLINE=\033[4m

#//////////////////////////////////////////////////////////////////////////////
#		RULES
#//////////////////////////////////////////////////////////////////////////////

all: $(NAME)

# Binary creation
$(NAME): $(OBJS) Makefile
	$(AR) $(NAME) $(OBJS)
	printf "\n$(GREEN)$(BOLD)Library $(NAME) created$(RESET)	✅\n"

$(P_OBJS)%.o: $(P_SRCS)%.c $(INCS) Makefile | $(P_OBJS)
	$(CC) $(CF) $(CI) -c $< -o $@
	printf "$(ERASE)$(FAINT)$(CC) $(CF) $(CI) -c -o $(RESET)$(CYAN)$(BOLD)$@$(RESET) $(FAINT)$(BLUE)$<$(RESET)"

$(P_OBJS):
	mkdir -p	$(P_OBJS)					$(P_OBJS)$(P_BOOLEANS)	\
				$(P_OBJS)$(P_CONVERSIONS)	$(P_OBJS)$(P_COUNTERS)	\
				$(P_OBJS)$(P_LISTS)			$(P_OBJS)$(P_MATHS)		\
				$(P_OBJS)$(P_MEMORY)		$(P_OBJS)$(P_PRINTS)	\
				$(P_OBJS)$(P_PROJECTS)		$(P_OBJS)$(P_STRINGS)
	printf "$(GREEN)$(BOLD)LIBFT obj directories created$(RESET)	✅\n"

# Mandatory rules

clean:
	$(RM) $(OBJS) $(P_OBJS)
	printf "$(YELLOW)$(BOLD)All LIBFT object files removed$(RESET)\n"

fclean: clean
	$(RM) $(NAME)
	printf "$(YELLOW)$(BOLD)All LIBFT object folders removed$(RESET)\n"
	printf "$(RED)$(BOLD)Library $(NAME) removed $(RESET)\n"

re:
	$(MAKE) fclean
	$(MAKE) all