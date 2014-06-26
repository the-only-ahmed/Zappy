# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/25 02:16:49 by jyim              #+#    #+#              #
#    Updated: 2014/06/26 20:56:11 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	@make -C serveur_src/
	@make -C client_src/
	@mv client_src/client .
	@mv serveur_src/serveur .

clean:
	@make -C client_src/ clean
	@make -C serveur_src/ clean

fclean: clean
	@make -C client_src/ fclean
	@make -C serveur_src/ fclean

re: fclean all
