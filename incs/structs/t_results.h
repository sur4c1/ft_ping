/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_results.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:36:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/25 16:43:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs/t_status.h"

typedef struct
{
	int			emited_packets;
	int			received_packets;
	float 		avg;
	float		max;
	float		min;
	float		stddev;
	t_status	status;
}	t_results;
