/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:36:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 18:23:39 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

void error(char *message, t_status status, bool print_usage)
{
	printf("ft_ping: %s\n", message);
	if (print_usage)
		usage();
	exit(status);
}
