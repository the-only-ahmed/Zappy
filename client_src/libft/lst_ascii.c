/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ascii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 21:16:39 by jyim              #+#    #+#             */
/*   Updated: 2014/05/14 20:35:45 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_l		*cons(char *src, t_l *first)
{
	t_l		*tmp;

	tmp = ft_lstnew(src);
	tmp->name = src;
	tmp->next = first;
	return (tmp);
}

t_l		*inser_tri(char *s1, t_l *first)
{
	if (first == NULL)
		return (cons(s1, first));
	else if (ft_strcmp(s1, first->name) < 0)
		return (cons(s1, first));
	else
		first->next = inser_tri(s1, first->next);
	return (first);
}
