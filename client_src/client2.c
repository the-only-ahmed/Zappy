/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/25 15:32:20 by jyim              #+#    #+#             */
/*   Updated: 2014/06/17 20:26:40 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "czap.h"

int		client_init(char *port, char *in)
{
	int							s;
	struct sockaddr_in			addr;
	struct hostent				*test;

	if ((s = socket(PF_INET, SOCK_STREAM, getprotobyname("tcp")->p_proto)) <= 0)
		return (-1);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(ft_atoi(port));
	test = gethostbyname(in);
	addr.sin_addr.s_addr =
		inet_addr(inet_ntoa(*((struct in_addr *)test->h_addr)));
	if (connect(s, (const struct sockaddr *)&addr, sizeof(addr)))
	{
		return (-1);
	}
	return (s);
}
