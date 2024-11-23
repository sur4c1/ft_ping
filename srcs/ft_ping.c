/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:57:16 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 15:46:42 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"
#include "ping.h"

t_bool	g_help 			= FALSE;
t_bool	g_verbose		= FALSE;
int		g_msgsz	= 56;

int	main(int argc, char *argv[])
{
	if (parse_arguments(argc, argv))
		return (64);
	while (ft_optind < argc)
	{
		ping(argv[ft_optind]);
		ft_optind++;
	}
	return (0);
}
