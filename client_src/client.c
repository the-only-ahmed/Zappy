/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 13:57:49 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 08:25:07 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void	init_fd2(t_env *e, int sock)
{
	e->max = sock;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(0, &e->fd_read);
	FD_SET(sock, &e->fd_read);
}

void	ft_write3(t_env *e, int s)
{
	int		r;
	char	buf[BUF_SIZE];

	(void)e;
	r = 0;
	if ((r = read(0, buf, BUF_SIZE)) <= 0)
	{
		ft_putendl("Read problem");
		exit(0);
	}
	buf[r] = '\0';
	send(s, buf, r, 0);
	ft_bzero(buf, r);
}

void	ft_read3(t_env *e, int s, t_play *p)
{
	char	buf[BUF_SIZE];
	int		r;

	(void)e;
	r = recv(s, buf, BUF_SIZE, 0);
	if (r <= 0)
	{
		exit(0);
	}
	if (!strncmp("BIENVENUE\n", buf, 10))
	{
		send(s, p->client.name, strlen(p->client.name), 0);
		p->action = add_act(p->client.name, p->action);
		p->auth++;
	}
	ft_parse(buf, s, p, e);
	ft_bzero(buf, r);
}

void	check_fd2(t_env *e, int sock, t_play *p)
{
	if (e->r)
	{
		if (FD_ISSET(sock, &e->fd_read))
			ft_read3(e, sock, p);
	}
}

int		main(int ac, char **av)
{
	int				sock;
	t_env			*e;
	t_client		client;

	if (ac < 3)
	{
		printf("Not enough arg\n");
		return (-1);
	}
	sock = 0;
	parse_client(av, ac, &client);
	e = (t_env *)malloc(sizeof(t_env));
	printf("%s et %s\n", client.host, client.port);
	client.name = ft_strjoin(client.name, "\n");
	init_client(sock, e, client);
	return (0);
}
