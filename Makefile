# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/04 14:32:18 by cbarbier          #+#    #+#              #
#    Updated: 2017/10/09 14:24:25 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
LIB				= libft/libft.a
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
HDR				= includes/minishell.h
SRCS			= srcs/main.c \
				srcs/init_mns.c \
				srcs/line_reader.c \
				srcs/treat_cmd.c \
				srcs/parse_token.c \
				srcs/tools.c \
				srcs/fr33.c \
				srcs/builtins/f_cd.c \
				srcs/builtins/f_echo.c \
				srcs/builtins/f_env.c \
				srcs/builtins/f_exit.c \
				srcs/builtins/f_setenv.c \
				srcs/builtins/f_unsetenv.c
OBJS			= $(SRCS:.c=.o)

all: visu $(NAME)

visu:
ifneq ($(shell test -e minishell;echo $$?), 0)
	@echo " / \   / \   / \   / \   / \   / \   / \   / \   / \ "
	@echo "( m ) ( i ) ( n ) ( i ) ( s ) ( h ) ( e ) ( l ) ( l )"
	@echo " \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/ "
endif

%.o:%.c $(HDR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I includes

$(NAME): $(LIB) $(OBJS) $(HDR)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft
	@echo "EXECUTABLE BUILT\t\033[0;32m✓\033[0m"

ifneq ($(shell make -q -C libft;echo $$?), 0)
.PHONY: $(LIB)
endif

$(LIB):
	@make -C libft

clean:
	@/bin/rm -rf $(OBJS)
	@make -C libft clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: clean fclean all re
