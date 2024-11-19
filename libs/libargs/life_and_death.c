/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_and_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:04:37 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/19 11:21:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libargs.h"
#include <string.h>

void	add_config(t_args_config **config, t_args_config option)
{
	t_args_config	*new_config;
	t_args_config	*ptr;
	new_config = malloc(sizeof (t_args_config));
	memcpy(new_config, &option, sizeof (t_args_config));
	if (!*config)
		*config = new_config;
	else
	{
		ptr = *config;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_config;
	}
}

void	free_config(t_args_config	*config)
{
	t_args_config	*nxt;

	while (config)
	{
		nxt = config->next;
		free(config);
		config = nxt;
	}
}

t_args	*parse(int argc, char **argv, t_args_config)
{
	t_args *args;
	int		positional_count;

	args = NULL;
	positional_count = 0;
	while (argc--)
	{
		argv++;
		if (strcmp(*argv, "--"))
			break;
		if (strncmp(*argv, "--", 2))
		{}
		else if (**argv == '-')
		{}
		else
		{}
	}
	while (argc--)
	{
		argv++;
	}
	return args;
}

void	free_args(t_args *args)
{
	t_args	*nxt;

	while (args)
	{
		nxt = args->next;
		free(args->value);
		free(args);
		args = nxt;
	}
}
