# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttremel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/10 13:35:36 by ttremel           #+#    #+#              #
#    Updated: 2025/03/24 13:54:48 by ttremel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	get_next_line.a
CC			=	cc
LIB			=	../libft.a
OBJ_PATH	=	./obj

SRCS		=	get_next_line.c			\
				get_next_line_utils.c

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g
else
	CFLAGS	=	-Wall -Wextra -Werror
endif

OBJS		=	$(SRCS:%.c=$(OBJ_PATH)/%.o)

all:	$(NAME)

$(OBJ_PATH)/%.o: %.c
	@(mkdir -p $(dir $@))
	@($(CC) -o $@ -c $< $(CFLAGS) )

$(NAME):	$(OBJS)
	@(ar -rc $(NAME) $(OBJS) $(LIB))

clean:
	@(rm -f $(OBJS))

fclean:
	@(rm -f $(NAME))

re:	fclean all

.PHONY: all clean fclean re