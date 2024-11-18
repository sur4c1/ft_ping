/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:25:00 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/25 11:53:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_strtab.h"
#include <stdlib.h>
#include <stdio.h>

void		strtab_push(t_strtab *chartab, char *str);
void		strtab_print(t_strtab chartab, char *prefix);
t_strtab	strtab_new(void);
void		strtab_del(t_strtab *chartab);

