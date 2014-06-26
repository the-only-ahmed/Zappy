/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 07:40:22 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 20:44:27 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void	parse_client(char **av, int ac, t_client *client)
{
	int		i;

	i = 1;
	client->name = NULL;
	client->port = NULL;
	client->host = NULL;
	while (i < ac)
	{
		if (!strcmp(av[i], "-n") && av[i + 1])
			client->name = strdup(av[i + 1]);
		else if (!strcmp(av[i], "-p") && av[i + 1])
			client->port = strdup(av[i + 1]);
		else if (!strcmp(av[i], "-h") && av[i + 1])
			client->host = strdup(av[i + 1]);
		i++;
	}
	if (client->host == NULL)
		client->host = strdup("localhost");
	if (client->port == NULL || client->name == NULL)
		exit(0);
}

void	ft_loop(int s, t_env *e, t_play p)
{
	while (42)
	{
		init_fd(e, s);
		e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
		if (p.wait)
			printf("DEBUT\n\n");
		check_fd2(e, s, &p);
	}
}

void	init_client(int s, t_env *e, t_client client)
{
	int		father;
	t_play	player;

	father = fork();
	if (father > 0)
		return ;
	if (father == 0)
	{
		if ((s = client_init(client.port, client.host)) < 0)
		{
			ft_putendl_fd("Client init error\n", 2);
			exit(0);
		}
		printf("SON\n");
		player = init_play(s, client);
		ft_loop(s, e, player);
	}
}
