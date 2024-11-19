/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 06:45:51 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/19 07:18:30 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libargs.h"

void	print_help(char *program_name, t_args_config *config)
{
	t_args_config	*ptr;

	printf("%s", program_name);
	ptr = config;
	while (ptr)
	{
		printf(" ");
		if (!ptr->is_option)
			continue;
		if (!ptr->is_mandatory)
			printf("[");
		printf("-%c|--%s", ptr->short_name, ptr->long_name);
		if (ptr->has_argument)
			printf("<%s>", ptr->argument_name);
		if (!ptr->is_mandatory)
			printf("]");
		ptr = ptr->next;
	}
}
