/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 01:45:25 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 08:08:50 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

t_inv	init_inventaire(void)
{
	t_inv	inv;

	inv.nourriture = 10;
	inv.linemate = 0;
	inv.sibur = 0;
	inv.mendiane = 0;
	inv.phiras = 0;
	inv.deraumere = 0;
	inv.thystame = 0;
	return (inv);
}

t_cond	init_cond_first(void)
{
	t_cond	c;

	c.linemate = 0;
	c.sibur = 0;
	c.mendiane = 0;
	c.phiras = 0;
	c.deraumere = 0;
	c.thystame = 0;
	return (c);
}

t_cond	init_cond(int lvl)
{
	t_cond	cond;

	cond = init_cond_first();
	if (lvl == 1)
	{
		cond.player = 1;
		cond.linemate = 1;
	}
	if (lvl == 2)
	{
		cond.player = 2;
		cond.linemate = 1;
		cond.deraumere = 1;
		cond.sibur = 1;
	}
	if (lvl == 3)
	{
		cond.player = 2;
		cond.linemate = 2;
		cond.phiras = 2;
		cond.sibur = 1;
	}
	cond = init_cond3(lvl, cond);
	cond = init_cond2(lvl, cond);
	return (cond);
}

t_play	init_the_play(t_play player)
{
	player.ask = 0;
	player.forking = 0;
	player.elev_n = 0;
	player.wait = 0;
	player.action = NULL;
	player.ret_action = NULL;
	player.forking = 0;
	player.elev = 0;
	player.lvl = 1;
	player.auth = 0;
	player.nb_req = 0;
	player.master = 0;
	player.hungry = 0;
	player.move = 0;
	player.temp = NULL;
	player.elevation_now = 0;
	player.wait = 0;
	player.searching = NULL;
	return (player);
}

t_play	init_play(int s, t_client c)
{
	t_play	player;
	int		i;

	(void)s;
	i = 0;
	while (i < 8)
	{
		player.condition[i] = init_cond(i);
		i++;
	}
	player.client = c;
	player.inventaire = init_inventaire();
	player.to_do = NULL;
	player.request = 0;
	player.curr = 0;
	player = init_the_play(player);
	return (player);
}
