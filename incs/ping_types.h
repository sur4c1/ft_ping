/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 09:22:28 by yyyyyy            #+#    #+#             */
/*   Updated: 2026/05/20 09:50:13 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define inout
typedef struct s_opt
{
	int count;
	int interval;
	int ttl;
	int timeout;
	int linger;
	int verbose;
} t_opt;
