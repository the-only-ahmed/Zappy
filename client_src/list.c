/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 20:51:18 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 09:18:48 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

t_act		*add_act(char *name, t_act *l)
{
	t_act	*tmp;
	t_act	*tmp2;

	tmp = (t_act *)malloc(sizeof(t_act));
	tmp->action = strdup(name);
	tmp->next = NULL;
	tmp->reponse = NULL;
	if (!l)
		return (tmp);
	tmp2 = l;
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	return (l);
}

t_act		*list_suppr(t_act *l)
{
	t_act	*tmp;

	if (!l)
		return (NULL);
	else if (l->next == NULL)
		return (NULL);
	tmp = l->next;
	if (l)
	{
		if (l->action)
			free(l->action);
		free(l);
		l = NULL;
	}
	return (tmp);
}

t_act		*add_first(char *cmd, t_act *l)
{
	t_act	*first;

	first = (t_act *)malloc(sizeof(t_act));
	first->action = strdup(cmd);
	first->next = l;
	return (first);
}

void		exec_list(t_play *p, int s)
{
	if (p->auth < 9 && p->ret_action)
	{
		p->auth++;
		send(s, p->ret_action->action, strlen(p->ret_action->action), 0);
		p->action = add_act(p->ret_action->action, p->action);
		p->ret_action = list_suppr(p->ret_action);
	}
}

int			count_liste(t_act *l)
{
	t_act	*tmp;
	int		i;

	i = 0;
	tmp = l;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
