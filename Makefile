# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/07/24 14:30:43 by ele-sage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -g -fsanitize=address
READLINE_DIR = $(shell brew --prefix readline)

READLINE_LIB = -lreadline -lhistory -L $(READLINE_DIR)/lib

# Directories
SRCDIR   	:= srcs
OBJDIR   	:= obj
INCDIR   	:= includes


################################### SOURCES ####################################
# Builtin
SRCFILES 	:=  builtin/cd.c builtin/echo.c builtin/env.c \

# Lexer
SRCFILES 	:=  lexer/lexer.c lexer/double_quotes.c \

# Parser
SRCFILES 	:=  parser/init_cmds_utils.c parser/init_cmds.c parser/parser.c \

# Expander
SRCFILES 	:=  expander/init_env_vars.c expander/expander.c \

# Executor
SRCFILES 	:=  executor/executor.c \

# Utils
SRCFILES 	:=  utils/error.c utils/free.c utils/unix_signals.c \

# Main
SRCFILES 	:=  main_loop.c main.c \



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

re: fclean all

.PHONY: all clean fclean re
