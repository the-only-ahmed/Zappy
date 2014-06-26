/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 17:31:17 by jyim              #+#    #+#             */
/*   Updated: 2013/11/24 19:46:48 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	int		cnt;

	i = ft_strlen(s1);
	cnt = 0;
	while (s2[cnt] != '\0' && n > 0)
	{
		s1[i] = s2[cnt];
		i++;
		cnt++;
		n--;
	}
	s1[i] = '\0';
	return (s1);
}
