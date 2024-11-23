NAME		=	ft_ping
LIBFT		=	libft.a

SRCS_DIR	=	srcs/
INCS_DIR	=	incs/
OBJS_DIR	=	objs/
LIBFT_DIR	=	./libs/libft/

SRCS_FILES	=	ft_ping	arguments ping
INCS_FILES	=	ft_ping	arguments ping

OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
INCS		=	$(addprefix $(INCS_DIR), $(addsuffix .h, $(INCS_FILES)))

SILENCER	=

CC			=	$(SILENCER)cc
CFLAGS		=	-Wall -Wextra -Werror -I $(INCS_DIR) -I $(LIBFT_DIR)
LDFLAGS		=	-L $(LIBFT_DIR) -lft

RM			=	$(SILENCER)rm -rf
MKDIR		=	$(SILENCER)mkdir -p
CHOWN		=	$(SILENCER)sudo chown
CHMOD		=	$(SILENCER)sudo chmod

all:			$(NAME)

clean:
	$(RM)	$(OBJS_DIR)

fclean:	clean
	$(RM)	$(NAME)

re:	fclean all

debug: CFLAGS += -fsanitize=address -g3
debug: re

$(NAME):		$(OBJS) $(INCS) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	$(CHOWN) root:root $(NAME)
	$(CHMOD) u+s $(NAME)

$(LIBFT_DIR)$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
	$(MKDIR) $(OBJS_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all re clean fclean debug
