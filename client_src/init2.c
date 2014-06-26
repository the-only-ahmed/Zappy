/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 07:49:25 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 07:49:44 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

t_cond	init_cond3(int lvl, t_cond cond)
{
	if (lvl == 4)
	{
		cond.player = 4;
		cond.linemate = 1;
		cond.deraumere = 1;
		cond.phiras = 1;
		cond.sibur = 2;
	}
	if (lvl == 5)
	{
		cond.player = 4;
		cond.linemate = 1;
		cond.deraumere = 2;
		cond.mendiane = 3;
		cond.sibur = 1;
	}
	return (cond);
}

t_cond	init_cond2(int lvl, t_cond cond)
{
	if (lvl == 6)
	{
		cond.player = 6;
		cond.linemate = 1;
		cond.deraumere = 2;
		cond.sibur = 3;
		cond.phiras = 1;
	}
	if (lvl == 7)
	{
		cond.player = 6;
		cond.linemate = 2;
		cond.deraumere = 2;
		cond.mendiane = 2;
		cond.sibur = 2;
		cond.phiras = 2;
		cond.thystame = 1;
	}
	return (cond);
}
