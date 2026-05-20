/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:02:46 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/21 05:52:09 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*res;

	if (!src)
		return (NULL);
	if (ft_strlen(src) <= n)
		return (ft_strdup(src));
	res = ft_calloc (n + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memmove(res, src, n);
	return (res);
}
