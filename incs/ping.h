/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:39:37 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/12/09 06:40:22 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ft_ping.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <math.h>

typedef struct s_packet_status
{
	struct timeval	send_time;
	struct timeval	recv_time;
	t_bool			is_recv;
}	t_packet_status;

t_error		ping(char *host);
