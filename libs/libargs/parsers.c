/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:26:37 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/19 10:36:50 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libargs.h"
#include <string.h>

void	*int_parser(char *str)
{
	int	*ret;
	ret = malloc(sizeof (int));
	if (ret)
		*ret = atoi(str);
	return ret;
}

void	*string_parser(char *str)
{
	return strdup(str);
}
