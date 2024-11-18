/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_status.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:47:18 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/25 16:26:18 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

typedef enum {
	OK,
	PARSE_ERROR = 2,
	ERR_SOCKET,
}	t_status;
