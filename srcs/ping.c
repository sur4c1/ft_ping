/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:39:04 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 14:52:42 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

t_error		ping(char *host)
{
	int					sockfd;
	ssize_t				n;
	struct sockaddr_in	dest_addr;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0)
	{
		perror("socket");
		return (ERROR);
	}
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = 0;
	dest_addr.sin_addr.s_addr = inet_addr(host);
	n = sendto(sockfd, "ping", 4, 0,
		(struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (n < 0)
	{
		perror("sendto");
		return (ERROR);
	}
	return (OK);
}
