/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:09:35 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/26 09:04:21 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"

t_error	parse_arguments(int argc, char *argv[])
{
	int			arg;
	int			longindx;
	t_option	options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{"help", no_argument, NULL, '?'},
		{"count", required_argument, NULL, 'c'},
		{"linger", required_argument, NULL, 'W'},
		{"interval", required_argument, NULL, 'i'},
		{NULL, no_argument, NULL, 0},
	};

	while ((arg = ft_getopt_long(argc, argv, "v?c:W:i:", options, &longindx)) != -1)
	{
		switch (arg)
		{
			case 'v':
				g_verbose = TRUE;
				break;
			case 'c':
				g_count = ft_atoi(ft_optarg);
				break;
			case 'W':
				g_linger = ft_atoi(ft_optarg);
				break;
			case 'i':
				g_interval = ft_atoi(ft_optarg);
				break;
			case '?':
				if (!ft_optopt)
					g_help = TRUE;
				else
					return (UKNOWN_OPTION);
		}
	}
	return (OK);
}
