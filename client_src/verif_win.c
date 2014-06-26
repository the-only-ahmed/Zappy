/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/22 03:20:38 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 09:11:06 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void	drop_res2(char *cmd, t_play *p, int s, int i)
{
	if (i == 0)
	{
		p->ret_action = add_first(cmd, p->ret_action);
		return ;
	}
	else if (i != 0)
	{
		p->move = 1;
		deplacement_to(i, s, p, cmd);
		return ;
	}
}

void	drop_res(t_play *p, char *buf, int s)
{
	int		i;
	char	**tab;
	char	*cmd;
	char	*ret;

	i = 0;
	if (!p->searching)
		return ;
	tab = ft_strsplit(buf, ',');
	while (tab[i])
	{
		if (strstr(tab[i], p->searching))
		{
			cmd = strdup("prend ");
			ret = ft_strjoin(p->searching, "\n");
			cmd = ft_strjoin(cmd, ret);
			free(ret);
			drop_res2(cmd, p, s, i);
			return ;
		}
		i++;
	}
}

void	verif_up2(t_play *p, int s)
{
	p->searching = NULL;
	p->elevation_now = 1;
	p->move = 1;
	p->ret_action = NULL;
	if (p->lvl == 1)
		end_alg(p);
	else
		give_pos(p, s);
}

void	verif_up(int s, t_play *p)
{
	t_cond	verif;
	t_inv	ret;

	ret = p->inventaire;
	verif = p->condition[p->lvl];
	if (ret.linemate < verif.linemate)
		p->searching = strdup("linemate");
	else if (ret.sibur < verif.sibur)
		p->searching = strdup("sibur");
	else if (ret.mendiane < verif.mendiane)
		p->searching = strdup("mendiane");
	else if (ret.phiras < verif.phiras)
		p->searching = strdup("phiras");
	else if (ret.deraumere < verif.deraumere)
		p->searching = strdup("deraumere");
	else if (ret.thystame < verif.thystame)
		p->searching = strdup("thystame");
	else
		verif_up2(p, s);
}
