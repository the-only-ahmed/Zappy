/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 09:02:15 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 09:34:15 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

int		verif_list2(char *buf, int s, t_play *p)
{
	char	**tab;

	(void)s;
	if (strcmp(p->action->action, "fin_elev\n") == 0)
	{
		tab = ft_strsplit(buf, ':');
		p->elevation_now = 0;
		p->move = 0;
		p->wait = 0;
		if (p->elev_n)
		{
			p->ret_action = NULL;
			p->elev_n = 0;
		}
		if (strcmp(buf, "ko\n"))
		{
			if (tab && tab[1])
				p->lvl = atoi(tab[1]);
		}
		p->action = list_suppr(p->action);
		return (1);
	}
	return (0);
}

int		verif_list3(char *buf, int s, t_play *p, t_env *e)
{
	if (strcmp(p->action->action, "incantation\n") == 0)
	{
		if (strstr(buf, "elevation en cours"))
		{
			p->action = add_act("fin_elev\n", p->action);
			p->elev_n = 1;
		}
		p->action = list_suppr(p->action);
		return (1);
	}
	if (strcmp(p->action->action, "connect_nbr\n") == 0)
	{
		if (atoi(buf) > 0)
		{
			init_client(s, e, p->client);
			p->forking = 0;
		}
		p->action = list_suppr(p->action);
		return (1);
	}
	return (0);
}

int		verif_list4(char *buf, int s, t_play *p)
{
	if (!strcmp(p->action->action, "voir\n"))
	{
		p->move = 0;
		p->action = list_suppr(p->action);
		drop_action(s, p, buf);
		recup_inv(s, p);
		return (1);
	}
	if (strstr(buf, "prend") && !strstr(buf, "nourriture"))
	{
		p->move = 0;
		p->searching = NULL;
		p->action = list_suppr(p->action);
		return (1);
	}
	if (strcmp(p->action->action, "prend nourriture\n") == 0)
	{
		p->move = 0;
		p->action = list_suppr(p->action);
		return (1);
	}
	return (0);
}
