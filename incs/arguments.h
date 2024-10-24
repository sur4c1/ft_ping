/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:08:22 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 18:24:05 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "structs/t_arguments.h"
#include "ft_error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

t_arguments	parse_arguments(char *argv[]);
void		print_arguments(t_arguments arguments);
