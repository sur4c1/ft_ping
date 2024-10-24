/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arguments.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:04:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 15:59:18 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <strtab.h>

enum e_options
{
	VERBOSE		= 0b1,
	HELP		= 0b01,
	FLOOD		= 0b001,
	PRELOAD		= 0b0001,
	NUMERIC		= 0b00001,
	TIMEOUT		= 0b000001,
	LINGER		= 0b0000001,
	PATERN		= 0b00000001,
	IGN_ROUTE	= 0b000000001,
	PCKT_SIZE	= 0b0000000001,
	TTL			= 0b00000000001,
	IP_TIMESTMP = 0b000000000001
};

typedef enum {
	TSONLY,
	TSADDR,
}	t_flag;

typedef struct {
	uint16_t	option_flags;
	t_strtab	destinations;
	int			preload;
	int			timeout;
	int			linger;
	char		pattern[16];
	int			packet_size;
	int			ttl;
	t_flag		ip_timestamp;
}	t_arguments;
