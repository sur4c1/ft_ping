/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:57:16 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 18:23:19 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	main(int argc, char *argv[])
{
	t_arguments	arguments;

	arguments = parse_arguments(argv);
	print_arguments(arguments);
	(void) argc;
	return (0);
}
