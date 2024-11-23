/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:39:37 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/23 14:50:53 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ft_ping.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

t_error		ping(char *host);
