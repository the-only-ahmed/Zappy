/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 08:53:30 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 09:43:06 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

int		ft_drop2(t_play *p, char **tab, int i2, int s)
{
	if (strstr(tab[i2], "nourriture"))
	{
		if (i2 == 0 && strstr(tab[i2], "linemate") && p->lvl == 1)
			p->ret_action = add_first("incantation\n", p->ret_action);
		if (i2 == 0)
		{
			p->ret_action = add_first("prend nourriture\n", p->ret_action);
			return (1);
		}
		else if (i2 != 0)
		{
			p->move = 1;
			printf("ET LA \n");
			deplacement_to(i2, s, p, "prend nourriture\n");
			printf("TRELELELEL\n");
			return (1);
		}
	}
	return (0);
}

void	drop_action(int s, t_play *p, char *buf)
{
	char	**tab;
	int		i2;

	i2 = 0;
	tab = ft_strsplit(buf, ',');
	if (p->hungry && p->move == 0)
	{
		while (tab[i2])
		{
			if (ft_drop2(p, tab, i2, s))
				return ;
			i2++;
		}
	}
}

void	maj_inv2(char **ret, t_play *p)
{
	if (strstr(ret[0], "nourriture"))
		p->inventaire.nourriture = atoi(ret[1]);
	else if (strstr(ret[0], "linemate"))
		p->inventaire.linemate = atoi(ret[1]);
	else if (strstr(ret[0], "sibur"))
		p->inventaire.sibur = atoi(ret[1]);
	else if (strstr(ret[0], "mendiane"))
		p->inventaire.mendiane = atoi(ret[1]);
	else if (strstr(ret[0], "phiras"))
		p->inventaire.phiras = atoi(ret[1]);
	else if (strstr(ret[0], "deraumere"))
		p->inventaire.deraumere = atoi(ret[1]);
	else if (strstr(ret[0], "thystame"))
		p->inventaire.thystame = atoi(ret[1]);
}

void	maj_inv(t_play *p, char *buf)
{
	char	**tab;
	char	**ret;
	int		i;

	i = 0;
	tab = ft_strsplit(buf, ',');
	while (tab[i])
	{
		ret = ft_strsplit(tab[i], ' ');
		if (ret && ret[0] && ret[1])
			maj_inv2(ret, p);
		i++;
	}
}

void	recup_inv(int s, t_play *p)
{
	exec_cmd_l(p, s, "inventaire\n");
}
