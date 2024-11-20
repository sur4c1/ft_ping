/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_and_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:04:37 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/20 08:22:31 by yyyyyy           ###   ########.fr       */
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

static
void	*double_free_args(t_args *a, t_args *b)
{
	free_args(a);
	free_args(b);
	return NULL;
}

t_args	*parse(int argc, char **argv, t_args_config *config)
{
	t_args			*args;
	t_args			*positionals;
	t_args_config	*found;
	char			*tmp;
	t_args			tmp_arg;

	args = NULL;
	positionals = NULL;
	while (argc--)
	{
		argv++;
		if (strcmp(*argv, "--"))
			break;
		if (strncmp(*argv, "--", 2))
		{
			found = find_config_long(config, *argv + 2);
			if (!found)
				return double_free_args(args, positionals);
			strcpy(tmp_arg.name, found->long_name);
			if (found->has_value)
			{
				if (!argc)
					return (double_free_args(args, positionals));
				tmp_arg.type = found->value_type;
				tmp_arg.value = found->parse_value(*(++argv));
				tmp_arg.type = found->value_type;
				argc--;
			}
			copy_end_arg(&args, tmp_arg);
		}
		else if (**argv == '-')
		{
			tmp = *argv;
			while (*++tmp)
			{
				found = find_config_shrt(config, *tmp);
				if (!found)
					return double_free_args(args, positionals);
				strcpy(tmp_arg.name, found->long_name);
				if (found->has_value)
				{
					if (!argc)
						return (double_free_args(args, positionals));
					tmp_arg.type = found->value_type;
					tmp_arg.value = found->parse_value(*(++argv));
					tmp_arg.type = found->value_type;
					argc--;
				}
			}
		}
		else
			copy_end_arg(&positionals, (t_args) {value: *argv});
	}
	while (argc--)
	{
		argv++;
		copy_end_arg(&positionals, (t_args) {value: *argv});
	}
	add_arg(&args, parse_positionals(positionals, config));
	free_args(positionals);
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
