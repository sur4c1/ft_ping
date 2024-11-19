/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 06:45:51 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/19 10:58:23 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libargs.h"
#include <string.h>

void	print_help(char *program_name, t_args_config *config)
{
	t_args_config	*ptr;
	char			brackets[3] = "[]";

	printf("\nUsage\n");
	printf("%s", program_name);
	ptr = config;
	while (ptr)
	{
		if (!ptr->is_option)
			continue;
		/*
			[-s|--long <value-name>]...
			#                      #     -> is optional
			          #############      -> has_value
			                        ###  -> repeat_mode APPEND
		 */
		printf(" ");
		if (!ptr->is_mandatory)
			ptrinf("[");
		ptrinf("-%c|--%s", ptr->short_name, ptr->long_name);
		if (ptr->has_value)
			printf(" <%s>", ptr->value_name);
		if (!ptr->is_mandatory)
			printf("]");
		if (ptr->repeat_mode == APPEND)
			ptrinf("...");
		ptr = ptr->next;
	}
	ptr = config;
	while (ptr)
	{
		if (ptr->is_option)
			continue;
		if (ptr->is_mandatory)
			strcpy(brackets, "<>");
		printf(" %c%s%c", brackets[0], ptr->long_name, brackets[1]);
		if (ptr->repeat_mode == APPEND)
			printf("...");
	}
	printf("\n");
}
