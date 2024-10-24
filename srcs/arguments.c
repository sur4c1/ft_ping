/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:09:35 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 18:23:02 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"

static
int	word_options(char *argv[], t_arguments *arguments)
{
	if (!strcmp(*argv, "verbose"))
		return (arguments->option_flags |= VERBOSE, 0);
	if (!strcmp(*argv, "help"))
		return (arguments->option_flags |= HELP, 0);
	if (!strcmp(*argv, "flood"))
		return (arguments->option_flags |= FLOOD, 0);
	if (!strcmp(*argv, "preload"))
	{
		if (!argv[1])
		{
			strtab_del(&arguments->destinations);
			error("option requires an argument -- 'timeout'", PARSE_ERROR, true);
		}
		arguments->timeout = atoi(argv[1]);
		return (arguments->option_flags |= TIMEOUT, 1);
	}
	if (!strcmp(*argv, "linger"))
	{
		if (!argv[1])
		{
			strtab_del(&arguments->destinations);
			error("option requires an argument -- 'linger'", PARSE_ERROR, true);
		}
		arguments->linger = atoi(argv[1]);
		return (arguments->option_flags |= LINGER, 1);
	}
	if (!strcmp(*argv, "pattern"))
	{
		if (!argv[1])
		{
			strtab_del(&arguments->destinations);
			error("option requires an argument -- 'pattern'", PARSE_ERROR, true);
		}
		strncpy(arguments->pattern, argv[1], 16);
		return (arguments->option_flags |= PATERN, 1);
	}
	if (!strcmp(*argv, "ignore-routing"))
		return (arguments->option_flags |= IGN_ROUTE, 0);
	if (!strcmp(*argv, "size"))
	{
		if (!argv[1])
		{
			strtab_del(&arguments->destinations);
			error("option requires an argument -- 'size'", PARSE_ERROR, true);
		}
		arguments->packet_size = atoi(argv[1]);
		return (arguments->option_flags |= PCKT_SIZE, 1);
	}
	if (!strcmp(*argv, "ttl"))
	{
		if (!argv[1])
			{
				strtab_del(&arguments->destinations);
				error("option requires an argument -- 'ttl'", PARSE_ERROR, true);
			}
		arguments->ttl = atoi(argv[1]);
		return (arguments->option_flags |= TTL, 1);
	}
	if (!strcmp(*argv, "ip-timestamp"))
	{
		if (!argv[1])
			{
				strtab_del(&arguments->destinations);
				error("option requires an argument -- 'ip-timestamp'", PARSE_ERROR, true);
			}
		if (strcmp(argv[1], "tsonly"))
			arguments->ip_timestamp = TSONLY;
		else if (strcmp(argv[1], "tsaddr"))
			arguments->ip_timestamp = TSADDR;
		else
			{
				strtab_del(&arguments->destinations);
				error("invalid argument -- 'ip-timestamp'", PARSE_ERROR, true);
			}
		return (arguments->option_flags |= IP_TIMESTMP, 1);
	}
	error("invalid option", PARSE_ERROR, true);
	return (0);
}

static
int letter_options(char *argv[], t_arguments *arguments)
{
	int used_args = 0;

	while (*++*argv)
	{
		if (**argv == 'v')
		{
			arguments->option_flags |= VERBOSE;
			continue;
		}
		if (**argv == 'h')
		{
			arguments->option_flags |= HELP;
			continue;
		}
		if (**argv == 'f')
		{
			arguments->option_flags |= FLOOD;
			continue;
		}
		if (**argv == 'l')
		{
			if (!argv[1])
			{
				strtab_del(&arguments->destinations);
				error("option requires an argument -- 'l'", PARSE_ERROR, true);
			}
			arguments->preload = atoi(argv[1]);
			arguments->option_flags |= PRELOAD;
			used_args++;
			continue;
		}
		if (**argv == 'n')
		{
			arguments->option_flags |= NUMERIC;
			continue;
		}
		if (**argv == 'w')
		{
			if (!argv[1])
				{
					strtab_del(&arguments->destinations);
					error("option requires an argument -- 'w'", PARSE_ERROR, true);
				}
			arguments->timeout = atoi(argv[1]);
			arguments->option_flags |= TIMEOUT;
			used_args++;
			continue;
		}
		if (**argv == 'W')
		{
			if (!argv[1])
				{
					strtab_del(&arguments->destinations);
					error("option requires an argument -- 'W'", PARSE_ERROR, true);
				}
			arguments->linger = atoi(argv[1]);
			arguments->option_flags |= LINGER;
			used_args++;
			continue;
		}
		if (**argv == 'p')
		{
			if (!argv[1])
				{
					strtab_del(&arguments->destinations);
					error("option requires an argument -- 'p'", PARSE_ERROR, true);
				}
			strncpy(arguments->pattern, argv[1], 16);
			arguments->option_flags |= PATERN;
			used_args++;
			continue;
		}
		if (**argv == 'r')
		{
			arguments->option_flags |= IGN_ROUTE;
			continue;
		}
		if (**argv == 's')
		{
			if (!argv[1])
				{
					strtab_del(&arguments->destinations);
					error("option requires an argument -- 's'", PARSE_ERROR, true);
				}
			arguments->packet_size = atoi(argv[1]);
			arguments->option_flags |= PCKT_SIZE;
			used_args++;
			continue;
		}
	}
	return (used_args);
}

t_arguments	parse_arguments(char *argv[])
{
	t_arguments	arguments;

	arguments.destinations = strtab_new();
	while (*++argv)
	{
		if (!strcmp(*argv, "--"))
			break;
		if (!strncmp(*argv, "--", 2))
		{
			(*argv) += 2;
			argv += word_options(argv, &arguments);
		}
		else if (**argv == '-')
		{
			(*argv) += 1;
			argv += letter_options(argv, &arguments);
		}
		else
			strtab_push(&arguments.destinations, *argv);
	}
	while (*argv && *++argv)
		strtab_push(&arguments.destinations, *argv);
	return (arguments);
}

void		print_arguments(t_arguments arguments)
{
	printf("Options: %d\n", arguments.option_flags);
	printf("Destinations:\n");
	strtab_print(arguments.destinations);
	printf("Preload: %d\n", arguments.preload);
	printf("Timeout: %d\n", arguments.timeout);
	printf("Linger: %d\n", arguments.linger);
	printf("Pattern: %s\n", arguments.pattern);
	printf("Packet size: %d\n", arguments.packet_size);
	printf("TTL: %d\n", arguments.ttl);
	printf("IP Timestamp: %d\n", arguments.ip_timestamp);
}
