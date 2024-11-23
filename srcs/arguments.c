/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:09:35 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 14:41:16 by yyyyyy           ###   ########.fr       */
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
		{NULL, no_argument, NULL, 0},
	};

	while ((arg = ft_getopt_long(argc, argv, "v?", options, &longindx)) != -1)
	{
		switch (arg)
		{
			case 'v':
				g_verbose = TRUE;
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
