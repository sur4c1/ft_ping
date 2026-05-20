/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __ft_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:11:54 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/26 06:47:45 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__ft_printf.h"

static
size_t	parse_arg(char *format, va_list ap, t_buff *buff)
{
	size_t	len;
	str		string;
	char	c;

	len = 1;
	if (ft_strncmp(format, "%s", 2) == 0)
	{
		string = va_arg(ap, str);
		*buff = ft_bufcat(*buff, (t_buff) {string, ft_strlen(string)});
		return (2);
	}
	else if (ft_strncmp(format, "%%", 2) == 0)
	{
		*buff = ft_bufcat(*buff, (t_buff) {"%", 1});
		return (2);
	}
	else if (ft_strncmp(format, "%c", 2) == 0)
	{
		c = va_arg(ap, int);
		*buff = ft_bufcat(*buff, (t_buff) {&c, 1});
		return (2);
	}
	return (len);
	(void) ap;
	(void) buff;
	(void) format;
}

static
int	parse_str(char *format, t_buff *buff)
{
	size_t	len;

	len = 0;
	while (format[len] && format[len] != '%')
		len++;
	*buff = ft_bufcat(*buff, (t_buff) {format, len});
	return (len);
}

void	__ft_printf(char *format, va_list ap, t_buff *buff)
{
	while (*format)
	{
		if (*format == '%')
			format += parse_arg(format, ap, buff);
		else
			format += parse_str(format, buff);
	}
	(void) ap;
}
