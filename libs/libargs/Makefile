# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 06:46:15 by yyyyyy            #+#    #+#              #
#    Updated: 2024/11/19 10:32:24 by yyyyyy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libargs.a

SRCS		=	print_help	parsers

OBJDIR		=	objs/
OBJS		=	$(addprefix $(OBJDIR), $(addsuffix .o, $(SRCS)))

SILENCER	=
AR			=	$(SILENCER)ar rcs
RM			=	$(SILENCER)rm -rf
CC			=	$(SILENCER)cc
MKDIR		=	$(SILENCER)mkdir -p

CFLAGS		=	-Wall -Wextra -Werror

$(NAME):	$(OBJS)
	$(AR) $@ $^

$(OBJDIR)%.o: %.c
	$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

all:		$(NAME)

re:			fclean all

clean:
	$(RM)	$(OBJDIR)

fclean:		clean
	$(RM)	$(NAME)

.PHONY:	re all clean fclean
