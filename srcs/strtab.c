/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:59:24 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/10/24 18:17:36 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strtab.h"

void	strtab_push(t_strtab *chartab, char *str)
{
	if (chartab->size == chartab->allocated)
	{
		chartab->allocated *= 2;
		chartab->tab = realloc(chartab->tab, (chartab->allocated * 2) * sizeof(char *));
	}
	chartab->tab[chartab->size++] = str;
}

void	strtab_print(t_strtab chartab)
{
	size_t	i;

	i = 0;
	while (i < chartab.size)
	{
		dprintf(2, "%s\n", chartab.tab[i]);
		i++;
	}
}

t_strtab	strtab_new(void)
{
	t_strtab	chartab;

	chartab.size = 0;
	chartab.allocated = 8;
	chartab.tab = malloc(sizeof(char *) * chartab.allocated);
	return (chartab);
}

void	strtab_del(t_strtab *chartab)
{
	free(chartab->tab);
}
