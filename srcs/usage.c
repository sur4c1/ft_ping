/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:38:35 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/25 14:34:59 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "usage.h"

void	usage(void)
{
	printf(
		"Usage:\n"
		"\tping [options] <destination>+\n"
		"\n"
		"OPTIONS:\n"
		"\t-v, --verbose\n"
		"\t-?, --help\n"
		"\t-f, --flood\n"
		"\t-l, --preload <preload>\n"
		"\t-n, --numeric\n"
		"\t-w, --timeout <N>\n"
		"\t-W, --linger <N>\n"
		"\t-p, --patern <pattern>\n"
		"\t-r, --ignore-routing\n"
		"\t-s, --size <packetsize>\n"
		"\t  , --ttl <N>\n"
		"\t  , --ip-timestamp <flag>\n"
	);
}

void	help(void)
{
	usage();
}
