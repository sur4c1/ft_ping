/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:09:35 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 16:16:41 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arguments.h"

t_arguments	parse_arguments(int argc, char *argv[])
{
	int			arg;
	t_arguments	arguments;
	t_option	options[] = {
		{
			
		}
	};

	while ((arg = ft_getopt_long()) != -1)
	{}
}
