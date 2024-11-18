/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:07:12 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/29 07:23:18 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_arguments.h"
#include "structs/t_results.h"
#include "usage.h"
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <netinet/ip_icmp.h>

void	execute(t_arguments arguments);
