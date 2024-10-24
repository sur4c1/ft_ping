/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:48:06 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 17:13:13 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs/t_status.h"
#include "usage.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void error(char *message, t_status status, bool print_usage);
