# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/07/14 19:38:27 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

#//////////////////////////////////////////////////////////////////////////////
#		ALL FILES
#//////////////////////////////////////////////////////////////////////////////

# Directories
P_SRCS		:=	srcs/
P_INCS		:=	includes/

SRC			:=	lexer/lexer.c \
				parser/parser_free.c \
				parser/parser_init.c \
				parser/parser.c \
				parser/valid_args.c \
				main.c

INC			:=	minishell.h \
				lexer.h \
				parser.h

# Sources
SRCS		:=	$(addprefix $(P_SRCS), $(SRC))

# Objects
OBJS		:=	$(SRCS:.c=.o)

# Includes
INCS		:=	$(addprefix $(P_INCS), $(INC))


#//////////////////////////////////////////////////////////////////////////////
#		FLAGS & TEXT MODIFIERS
#//////////////////////////////////////////////////////////////////////////////

# Compilation
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -fsanitize=address -g3 -lreadline
INCFLAGS	:=	-I $(P_INCS)
LIBFLAGS	:=	-L libft -lft

# Text modifiers
DEFAULT		:=	\033[0m
BOLD		:=	\033[1m
DIM			:=	\033[2m
ITALIC		:=	\033[3m
UNDERLINE	:=	\033[4m
BLINK		:=	\033[5m
REVERSE		:=	\033[7m
HIDDEN		:=	\033[8m

# Colors
BLACK		:=	\033[30m
RED			:=	\033[31m
GREEN		:=	\033[32m
YELLOW		:=	\033[33m
BLUE		:=	\033[34m
MAGENTA		:=	\033[35m
CYAN		:=	\033[36m
WHITE		:=	\033[37m

#//////////////////////////////////////////////////////////////////////////////
#		RULES
#//////////////////////////////////////////////////////////////////////////////

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME)$(DEFAULT)$(GREEN) created.$(DEFAULT)"

%.o: %.c $(INCS)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
	@echo "$(GREEN)$(BOLD)$(notdir $<)$(DEFAULT)$(GREEN) created.$(DEFAULT)"

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "$(YELLOW)$(BOLD)$(NAME)$(DEFAULT)$(YELLOW) objects deleted.$(DEFAULT)"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(RED)$(BOLD)$(NAME)$(DEFAULT)$(RED) deleted.$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re 
