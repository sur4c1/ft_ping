# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 06:46:15 by yyyyyy            #+#    #+#              #
#    Updated: 2024/11/19 07:01:57 by yyyyyy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libargs.a

SRCS		=	print_help

OBJS		=	$(addsuffix .o, $(SRCS))
OBJDIR		=	objs/

SILENCER	=
AR			=	$(SILENCER)ar rcs
RM			=	$(SILENCER)rm -rf
CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

$(NAME):	$(OBJS)
	$(AR) $@ $^

$(OBJDIR)%.o: %.c
	$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $<

all:		$(NAME)

re:			fclean all

clean:
	$(RM)	$(OBJDIR)

fclean:		clean
	$(RM)	$(NAME)

.PHONY:	re all clean fclean
