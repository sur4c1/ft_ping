/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:09:35 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/05/20 11:58:07 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include <limits.h>

static void print_help(void)
{
	printf("Usage: ft_ping [OPTION...] HOST ...\n"
		   "Send ICMP ECHO_REQUEST packets to network hosts.\n"
		   "\n"
		   " Options valid for all request types:\n"
		   "\n"
		   "  -c, --count=NUMBER         stop after sending NUMBER packets\n"
		   "  -i, --interval=NUMBER      wait NUMBER seconds between sending each packet\n"
		   "      --ttl=N                specify N as time-to-live\n"
		   "  -v, --verbose              verbose output\n"
		   "  -w, --timeout=N            stop after N seconds\n"
		   "  -W, --linger=N             number of seconds to wait for response\n"
		   "\n"
		   "  -?, --help                 give this help list\n"
		   "      --usage                give a short usage message\n"
		   "  -V, --version              print program version\n"
		   "\n"
		   "Mandatory or optional arguments to long options are also mandatory or optional\n"
		   "for any corresponding short options.\n"
		   "\n"
		   "Options marked with (root only) are available only to superuser.\n"
		   "\n"
		   "Report bugs to <bug-inetutils@gnu.org>.\n");
}

static void print_usage(void)
{
	printf("Usage: ft_ping [-v?V] [-i NUMBER] [-w N] [-W N] [--count=NUMBER]\n"
		   "               [--interval=NUMBER] [--ttl=N] [--verbose] [--timeout=N]\n"
		   "               [--linger=N] [--help] [--usage] [--version]\n"
		   "               HOST ...\n");
}

static void print_version(void)
{
	printf("blavlal\n");
}

static void invalid_value(char *value)
{
	printf("ft_ping: invalid value (`%s' near `%s')\n", value, value);
}

static int is_num(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	return (*str);
}

int parse_arguments(int argc, char *argv[], inout t_opt *opt)
{
	int arg;
	t_option longopts[] = {
		{"count", required_argument, NULL, 'c'},
		{"interval", required_argument, NULL, 'i'},
		{"ttl", required_argument, NULL, 0xFF + 't'},
		{"verbose", no_argument, NULL, 'v'},
		{"timeout", required_argument, NULL, 'w'},
		{"linger", required_argument, NULL, 'W'},
		{"help", no_argument, NULL, '?'},
		{"usage", no_argument, NULL, 0xFF + 'u'},
		{"version", no_argument, NULL, 'V'},
	};

	while ((arg = ft_getopt_long(argc, argv, "c:i:vw:W:?V", longopts, NULL)) > 0)
	{
		switch (arg)
		{
		case 'c':
			if (!is_num(ft_optarg))
				invalid_value(ft_optarg);
			opt->count = ft_atoi(ft_optarg);
			break;
		case 'i':
			if (!is_num(ft_optarg))
				invalid_value(ft_optarg);
			opt->interval = ft_atoi(ft_optarg);
			break;
		case 0xFF + 't':
			if (!is_num(ft_optarg))
				invalid_value(ft_optarg);
			opt->ttl = ft_atoi(ft_optarg);
			break;
		case 'v':
			opt->verbose = TRUE;
			break;
		case 'w':
			if (!is_num(ft_optarg))
				invalid_value(ft_optarg);
			opt->timeout = ft_atoi(ft_optarg);
			break;
		case 'W':
			if (!is_num(ft_optarg))
				invalid_value(ft_optarg);
			opt->linger = ft_atoi(ft_optarg);
			break;
		case 'V':
			print_version();
			exit(0);
		case 0xFF + 'u':
			print_usage();
			exit(0);
		case '?':
			if (ft_optopt)
			{
				printf("Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
				return (64);
			}
			print_help();
			exit(0);
		default:
			break;
		}
	}
	if (ft_optind >= argc)
	{
		printf("ft_ping: missing host operand\n"
			   "Try 'ft_ping --help' or 'ft_ping --usage' for more information.\n");
		return (64);
	}
	return (0);
}
