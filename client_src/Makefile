# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/19 00:49:21 by jyim              #+#    #+#              #
#    Updated: 2014/06/26 21:02:20 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client

SRC = client.c client2.c reception.c pathfind.c list.c init.c verif_win.c \
	  begin_alg.c client3.c init2.c list2.c pathfind2.c pathfind3.c \
	  pathfind4.c pathfind5.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc -o $(NAME) $(OBJ) -L libft/ -lft -ltermcap

%.o: %.c
	gcc -Wall -Werror -Wextra -g3 -c -I libft/ -I. $<

clean:
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f ../$(NAME)
	@make -C libft/ fclean

re: fclean all
