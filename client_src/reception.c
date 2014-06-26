/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/13 14:41:58 by jyim              #+#    #+#             */
/*   Updated: 2014/06/13 14:53:02 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void	init_fd(t_env *e, int sock)
{
	e->max = sock;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(0, &e->fd_read);
	FD_SET(sock, &e->fd_read);
}

void	ft_read2(t_env *e, int s)
{
	char	buf[BUF_SIZE];
	int		r;

	(void)e;
	r = recv(s, buf, BUF_SIZE, 0);
	if (r <= 0)
	{
		ft_putendl("Recv problem");
		exit(0);
	}
	write(1, buf, r);
	ft_bzero(buf, r);
}

void	check_fd(t_env *e, int sock)
{
	if (e->r)
	{
		if (FD_ISSET(sock, &e->fd_read))
			ft_read2(e, sock);
	}
}
