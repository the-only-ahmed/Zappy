/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 08:45:34 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 09:59:16 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

int		count_list_act(t_act *l)
{
	int		i;
	t_act	*tmp;

	i = 0;
	if (!l)
		return (0);
	tmp = l;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	exec_cmd_l(t_play *p, int s, char *cmd)
{
	(void)s;
	p->ret_action = add_act(cmd, p->ret_action);
}

void	pathfind(int dir, t_play *p, int s)
{
	(void)s;
	if (dir == 2 || dir == 1 || dir == 8)
		p->ret_action = add_first("avance\n", p->ret_action);
	else if (dir == 3 || dir == 4 || dir == 5)
		p->ret_action = add_first("gauche\n", p->ret_action);
	else if (dir == 7 || dir == 6)
		p->ret_action = add_first("droite\n", p->ret_action);
}

int		count_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	find_mid(int i, t_move *m)
{
	int		ret;
	int		ret2;

	ret = 2;
	ret2 = 0;
	while (m->middle < i)
	{
		m->avant++;
		m->middle += ret;
		ret2 = ret;
		ret += 2;
		if (m->middle + (ret2 / 2) >= i && i >= ret)
		{
			m->dir = 1;
			m->lat = i - m->middle;
			return ;
		}
	}
	m->dir = -1;
	m->lat = m->middle - i;
	return ;
}
