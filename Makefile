# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/04 14:32:18 by cbarbier          #+#    #+#              #
#    Updated: 2017/06/26 17:50:49 by cbarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
LIB				= libft/libft.a
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
HDR				= includes/minishell.h
SRCS			= srcs/main.c 
OBJS			= $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I includes

$(NAME): $(LIB) $(OBJS) $(HDR)
	@echo " / \   / \   / \   / \   / \   / \   / \   / \   / \ "
	@echo "( m ) ( i ) ( n ) ( i ) ( s ) ( h ) ( e ) ( l ) ( l )"
	@echo " \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/   \_/ "
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -Llibft -lft
	@echo "EXECUTABLE BUILT\t\t\033[0;32m✓\033[0m"

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
