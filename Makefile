NAME		=	ft_ping

SRCS_DIR	=	srcs/
INCS_DIR	=	incs/
OBJS_DIR	=	objs/

SRCS_FILES	=	ft_ping	arguments	error	usage strtab	execute
INCS_FILES	=	ft_ping	arguments	execute	ft_error	strtab	usage			\
				structs/t_arguments	structs/t_status	structs/t_strtab

OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
INCS		=	$(addprefix $(INCS_DIR), $(addsuffix .h, $(INCS_FILES)))

SILENCER	=

CC			=	$(SILENCER)cc
CFLAGS		=	-Wall -Wextra -Werror -I $(INCS_DIR)

RM			=	$(SILENCER)rm -rf
MKDIR		=	$(SILENCER)mkdir -p
CHOWN		=	$(SILENCER)sudo chown
CHMOD		=	$(SILENCER)sudo chmod

all:			$(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean:	clean
	$(RM)	$(NAME)

re:	fclean all

debug: CFLAGS += -fsanitize=address -g3
debug: re

$(NAME):		$(OBJS) $(INCS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	$(CHOWN) root:root $(NAME)
	$(CHMOD) u+s $(NAME)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
	$(MKDIR) $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all re clean fclean debug
