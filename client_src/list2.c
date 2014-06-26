/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/26 07:54:01 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 07:55:05 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

void		print_list(t_act *l)
{
	if (!l)
		return ;
	else
	{
		printf("LIST = %s\n", l->action);
		print_list(l->next);
	}
}

t_act		*add_end_list(t_act *temp, t_act *act)
{
	t_act	*ret;
	t_act	*tmp2;

	if (!temp)
	{
		return (act);
	}
	while (temp)
	{
		ret = add_act(temp->action, ret);
		temp = temp->next;
	}
	tmp2 = ret;
	while (tmp2->next)
		tmp2 = tmp2->next;
	if (!act)
		return (tmp2);
	tmp2->next = act;
	print_list(ret);
	return (ret);
}
