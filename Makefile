# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/09/05 09:38:44 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# How to install readline:
# 1. brew install readline
# 2. brew link --force readline

NAME		:=	minishell
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -g -fsanitize=address
READLINE_DIR = $$HOME/goinfre/.brew/opt/readline

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

# Directories
SRCDIR   	:= srcs
OBJDIR   	:= obj
INCDIR   	:= includes


################################### SOURCES ####################################
SRCFILES 	:=  lexer/lexer.c lexer/norm.c\
				parser/init_cmds.c parser/parser.c \
				expander/init_env_vars.c expander/expander.c expander/quotes_utils.c \
				executor/executor.c executor/fd_utils.c executor/heredoc.c \
				executor/redir.c executor/exec_bin.c \
				utils/error.c utils/free.c utils/unix_signals.c utils/strjoinfree.c \
				main_loop.c main.c \
				builtin/env.c builtin/echo.c builtin/cd.c builtin/export.c \
				builtin/unset.c builtin/pwd.c builtin/exit.c \


SRCFILES 	:= $(addprefix $(SRCDIR)/,$(SRCFILES))
OBJFILES 	:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
INCS    	:= -Iincludes -I$(READLINE_DIR)/include -Ilibft/include -I$(INCDIR)

# Rules
# Compilation
$(NAME): $(OBJFILES)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJFILES) -L libft -lft $(READLINE_LIB) -o $(NAME)
	@echo "Minishell created."

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@

# Cleaning Up
clean:
	@rm -rf $(OBJDIR)
	@make clean -C libft
	@echo "Objects deleted."

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo "Minishell deleted."

re: fclean $(NAME)

val: 
	@make
	@valgrind --leak-check=full --trace-children=yes --track-fds=yes --suppressions=suppress --show-leak-kinds=all --log-file="leaks" ./minishell

.PHONY: $(NAME) clean fclean re