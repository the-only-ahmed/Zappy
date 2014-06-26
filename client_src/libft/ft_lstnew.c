/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 19:26:48 by jyim              #+#    #+#             */
/*   Updated: 2014/05/14 20:34:27 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_l		*ft_lstnew(void const *content)
{
	t_l		*new;

	new = (t_l *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->name = ft_strdup((char *)content);
	new->next = NULL;
	return (new);
}
