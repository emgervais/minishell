# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-sage <ele-sage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 12:33:49 by ele-sage          #+#    #+#              #
#    Updated: 2023/07/24 15:41:39 by ele-sage         ###   ########.fr        #
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
SRCFILES 	:=  lexer/lexer.c lexer/double_quotes.c \
				parser/init_cmds_utils.c parser/init_cmds.c parser/parser.c \
				expander/init_env_vars.c expander/expander.c \
				executor/executor.c \
				utils/error.c utils/free.c utils/unix_signals.c \
				main_loop.c main.c \



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
