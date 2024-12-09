/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:57:16 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/12/09 06:34:11 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "arguments.h"
#include "ping.h"

/*	OPTIONS
 */
t_bool	g_help 			= FALSE;
t_bool	g_verbose		= FALSE;
s32		g_count			= -1;
int		g_msgsz			= 56;
time_t	g_linger		= 10;
time_t	g_interval		= 1;
str		g_patern		= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int		g_ttl			= 64;

/*	SIGNALS
 */
t_bool	g_stop			= FALSE;

void	sig_handler(int signum)
{
	(void)signum;
	g_stop = TRUE;
}

static
void	print_help(char *name)
{
	printf("Usage: %s [OPTION]... DESTINATION\n", name);
	printf("Send ICMP ECHO_REQUEST packets to network hosts\n");
	printf("\n");
	printf("\t-v,\t--verbose\t\tverbose output\n");
	printf("\t-?,\t--help\t\t\tdisplay this help and exit\n");
	printf("\t-c,\t--count=NUMBER\t\tstop after sending NUMBER ECHO_REQUEST packets\n");
	printf("\t-W,\t--linger=NUMBER\t\twait NUMBER seconds for response\n");
	printf("\t-i,\t--interval=NUMBER\twait NUMBER seconds between sending each packet\n");
	printf("\t\t--ttl=NUMBER\t\tspecify NUMBER as time to live\n");
}

int	main(int argc, char *argv[])
{
	if (parse_arguments(argc, argv))
	{
		print_help(argv[0]);
		return (64);
	}
	signal(SIGINT, sig_handler);
	if (g_help)
	{
		print_help(argv[0]);
		return (0);
	}
	if (ft_optind == argc)
	{
		dprintf(2, "%s: missing host operand\n", argv[0]);
		dprintf(2, "Try '%s --help' for more information.\n", argv[0]);
		return (64);
	}
	while (ft_optind < argc)
	{
		if (ping(argv[ft_optind]))
			return (1);
		ft_optind++;
	}
	return (0);
}
