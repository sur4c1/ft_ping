/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libargs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 06:16:58 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/19 10:50:24 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum
{
	NONE,
	INT,
	STRING,
}	t_type;

typedef enum
{
	ERROR,
	OVERRIDE,
	APPEND,
}	t_repeat_mode;

void	*int_parser(char *);
void	*string_parser(char *);
void	*(*g_parsers[3])(char *) = {
	[NONE] = NULL,
	[INT] = int_parser,
	[STRING] = string_parser,
};

typedef struct	s_args_config
{
	char				long_name[128];
	bool				is_mandatory;
	t_repeat_mode		repeat_mode;

	bool				is_option;
	bool				has_value;
	char				short_name;
	char				value_name[64];
	char				description[512];
	t_type				value_type;
	void				*(*parse_value)(char *);
	void				(*free_value)(void *);

	struct s_args_config	*next;
}	t_args_config;

typedef struct	s_args
{
	char			name[128];
	void			*value;
	t_type			type;
	struct s_args	*next;
}	t_args;

void	print_help(char *program_name, t_args_config *config);
void	add(t_args_config **config, t_args_config new_config);
void	free_config(t_args_config *config);
t_args	*parse(int argc, char **argv, t_args_config *config);
void	free_args(t_args *args);
void	*get_value(t_args *args, char *key);
