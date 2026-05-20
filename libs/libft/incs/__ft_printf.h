/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 07:34:46 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/26 05:14:13 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_printf.h"
#include "ft_buff.h"
#include "ft_memory.h"
#include "ft_string.h"
#include "ft_types.h"
#include <stdarg.h>

#define __FLAGS		"-0# +"
#define __TYPES		"diouxXeEfFgGaAcspn%"
#define __LENMOD	{ "hh", "h", "ll", "l", "L", "j", "z", "t" }

typedef	struct s_conversion
{
	int		arg_index;
	t_bool	alternate_form;
	t_bool	zero_padding;
	t_bool	left_justify;
	t_bool	space_for_positive;
	t_bool	always_sign;
	size_t	minimal_width;
	size_t	precision;
}	t_conversion;

void	__ft_printf(char *format, va_list ap, t_buff *buff);
