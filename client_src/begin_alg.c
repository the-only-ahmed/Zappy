/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/22 06:27:03 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 07:44:16 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void	end_alg2(t_play *p, t_cond verif)
{
	while (verif.sibur)
	{
		p->ret_action = add_first("pose sibur\n", p->ret_action);
		verif.sibur--;
	}
	while (verif.mendiane)
	{
		p->ret_action = add_first("pose mendiane\n", p->ret_action);
		verif.mendiane--;
	}
	while (verif.phiras)
	{
		p->ret_action = add_first("pose phiras\n", p->ret_action);
		verif.phiras--;
	}
	while (verif.deraumere)
	{
		p->ret_action = add_first("pose deraumere\n", p->ret_action);
		verif.deraumere--;
	}
	while (verif.thystame)
	{
		p->ret_action = add_first("pose thystame\n", p->ret_action);
		verif.thystame--;
	}
}

void	end_alg(t_play *p)
{
	t_cond	verif;
	char	*cmd;

	p->ret_action = NULL;
	cmd = ft_strjoin("broadcast commencement.", ft_itoa(p->lvl));
	cmd = ft_strjoin(cmd, "\n");
	verif = p->condition[p->lvl];
	p->ret_action = add_first("incantation\n", p->ret_action);
	if (p->lvl > 1)
		p->ret_action = add_first(cmd, p->ret_action);
	while (verif.linemate)
	{
		p->ret_action = add_first("pose linemate\n", p->ret_action);
		verif.linemate--;
	}
	end_alg2(p, verif);
}

void	give_pos(t_play *p, int s)
{
	char	*cmd;
	char	*ret;

	p->wait = 0;
	ret = ft_itoa(p->lvl);
	ret = ft_strjoin(ret, "\n");
	cmd = ft_strjoin("broadcast begin.", ret);
	exec_cmd_l(p, s, cmd);
}
