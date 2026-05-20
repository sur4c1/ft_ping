/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 08:49:24 by bguyot            #+#    #+#             */
/*   Updated: 2024/11/23 15:59:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUT_H
# define FT_PUT_H

# include <unistd.h>
# include "ft_string.h"

/* Write the char c in the given fd */
void	ft_putchar_fd(char c, int fd);

/* Write the string s in the given fd */
void	ft_putstr_fd(char *s, int fd);

/* Write the string s in the given fd with a line break */
void	ft_putendl_fd(char *s, int fd);

/* Write a strnig representing n in the given fd */
void	ft_putnbr_fd(int n, int fd);

/* Write all the string of tab (NULL terminated) into fd */
void	ft_puttab_fd(char **tab, int fd);

/**
 * @brief Write the data of size size in the given fd
 * @note The data is printed in hexadecimal and ascii
 */
void	ft_putdata_fd(void *data, size_t size, int fd);

#endif
