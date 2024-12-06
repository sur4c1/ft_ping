/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:26 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/12/06 16:18:10 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <signal.h>

extern t_bool	g_verbose;
extern t_bool	g_help;
extern int		g_msgsz;
extern s32		g_count;
extern time_t	g_linger;
extern time_t	g_interval;
extern str		g_patern;
extern int 		g_ttl;

extern t_bool	g_stop;
