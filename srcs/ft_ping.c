/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:57:16 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/05/20 09:43:57 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "arguments.h"
#include "ping.h"

/*	OPTIONS
 */
t_bool g_help = FALSE;
t_bool g_verbose = FALSE;
s32 g_count = -1;
int g_msgsz = 56;
time_t g_linger = 10;
time_t g_interval = 1;
str g_patern = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int g_ttl = 64;

/*	SIGNALS
 */
t_bool g_stop = FALSE;

void sig_handler(int signum)
{
	(void)signum;
	g_stop = TRUE;
}

int main(int argc, char *argv[])
{
	t_opt opt;

	if (parse_arguments(argc, argv, &opt))
		return (64);
	signal(SIGINT, sig_handler);
	while (ft_optind < argc)
	{
		if (ping(argv[ft_optind], opt))
			return (1);
		ft_optind++;
	}
	return (0);
}
