/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arguments.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:04:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 18:36:59 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <strtab.h>
#include <sys/time.h>

enum e_options
{
	VERBOSE		= 0b1,
	HELP		= 0b10,
	FLOOD		= 0b100,
	PRELOAD		= 0b1000,
	NUMERIC		= 0b10000,
	TIMEOUT		= 0b100000,
	LINGER		= 0b1000000,
	PATERN		= 0b10000000,
	IGN_ROUTE	= 0b100000000,
	PCKT_SIZE	= 0b1000000000,
	TTL			= 0b10000000000,
	IP_TIMESTMP = 0b100000000000
};

typedef enum {
	TSONLY,
	TSADDR,
}	t_flag;

typedef struct {
	uint16_t	option_flags;
	t_strtab	destinations;
	int			preload;
	int			linger;
	int			timeout;
	char		pattern[16];
	int			packet_size;
	int			ttl;
	t_flag		ip_timestamp;
}	t_arguments;
