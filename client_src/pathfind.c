/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 13:03:40 by jyim              #+#    #+#             */
/*   Updated: 2014/06/26 10:14:07 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

int		verif_list5(char *buf, t_play *p)
{
	if (strcmp(p->action->action, "inventaire\n") == 0)
	{
		maj_inv(p, buf);
		p->action = list_suppr(p->action);
		return (1);
	}
	if (strstr(p->action->action, "broadcast") == 0)
	{
		printf("BUF = %s\n", buf);
		p->action = list_suppr(p->action);
		return (1);
	}
	return (0);
}

int		verif_support(t_play *p)
{
	p->action = list_suppr(p->action);
	p->action = add_act("nb\n", p->action);
	return (-1);
}

int		verif_list(char *buf, int s, t_play *p, t_env *e)
{
	printf("B=%s AC=%s ET A%d\n", buf, p->action->action, p->auth);
	if (p->action && p->action->action && !strstr(buf, "message"))
	{
		p->auth--;
		if (strstr(p->action->action, p->client.name))
			return (verif_support(p));
		if (!strcmp("nb\n", p->action->action))
		{
			if (atoi(buf) > 0)
				init_client(s, e, p->client);
			p->action = list_suppr(p->action);
			return (1);
		}
		if (verif_list2(buf, s, p))
			return (0);
		if (verif_list3(buf, s, p, e))
			return (0);
		if (verif_list4(buf, s, p))
			return (0);
		if (verif_list5(buf, p))
			return (0);
		else
			p->action = list_suppr(p->action);
	}
	return (0);
}

void	drop_some(int s, t_play *p)
{
	exec_cmd_l(p, s, "voir\n");
}

void	ft_parse(char *buf, int s, t_play *p, t_env *e)
{
	if (!strcmp(buf, "mort\n"))
	{
		print_list(p->action);
		printf("MORT\n");
		exit(0);
	}
	if (verif_list(buf, s, p, e) == -1)
		return ;
	p->hungry = 1;
	if (!p->move)
		drop_some(s, p);
	else
		recup_inv(s, p);
	exec_list(p, s);
}
