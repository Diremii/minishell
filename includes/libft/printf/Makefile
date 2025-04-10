# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttremel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 09:59:39 by ttremel           #+#    #+#              #
#    Updated: 2025/04/10 13:15:04 by ttremel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a
CC			=	cc
LIB			=	../libft.a
OBJ_PATH	=	./obj

SRCS		=	ft_printf.c			\
				ft_strlenf.c		\
				ft_num_count.c		\
				ft_args.c			\
				ft_putuint_fd.c		\
				ft_uint_count.c		\
				ft_putbaseuint_fd.c	\
				ft_ubase_count.c	\
				ft_sizeaddress.c	\
				ft_putaddress_fd.c	\
				print_putstr_fd.c

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -fPIE -g
else
	CFLAGS	=	-Wall -Wextra -Werror -fPIE
endif

OBJS		=	$(SRCS:%.c=$(OBJ_PATH)/%.o)

$(NAME):	$(OBJS)
	@(ar -rc $(NAME) $(OBJS) $(LIB))

all:	$(NAME)
	
$(OBJ_PATH)/%.o: %.c
	@(mkdir -p $(dir $@))
	@($(CC) -o $@ -c $< $(CFLAGS) )

clean:
	@(rm -f $(OBJS))

fclean:	clean
	@(rm -f $(NAME))

re:	fclean all

.PHONY: all clean fclean re
