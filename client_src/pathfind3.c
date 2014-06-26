/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 08:49:19 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 10:01:12 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void	request2_ft(t_move *m, t_play *p)
{
	int		i2;

	i2 = 0;
	if (m->dir == -1)
	{
		p->temp = add_act("gauche\n", p->temp);
		while (i2 < m->lat)
		{
			p->temp = add_act("avance\n", p->temp);
			i2++;
		}
	}
	else
	{
		p->temp = add_act("droite\n", p->temp);
		while (i2 < m->lat)
		{
			p->temp = add_act("avance\n", p->temp);
			i2++;
		}
	}
}

void	request_move(t_move *m, int s, t_play *p)
{
	int		i;

	i = 0;
	(void)s;
	p->temp = NULL;
	printf("JE SUIS ICI\n");
	printf("ALORS %d et %d\n", m->avant, m->lat);
	printf("FIN\n");
	while (i < m->avant)
	{
		p->temp = add_act("avance\n", p->temp);
		i++;
	}
	request2_ft(m, p);
	p->temp = add_act(m->request, p->temp);
	p->move = 0;
	printf("BORDELLL \n");
	p->ret_action = add_end_list(p->temp, p->ret_action);
}

void	deplacement_to(int i, int s, t_play *p, char *cmd)
{
	t_move		m;

	m.dir = 0;
	m.avant = 0;
	m.middle = 0;
	m.lat = 0;
	m.request = strdup(cmd);
	find_mid(i, &m);
	request_move(&m, s, p);
	printf("ET LO ? \n");
	print_list(p->ret_action);
}
