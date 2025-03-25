# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttremel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 16:08:13 by ttremel           #+#    #+#              #
#    Updated: 2025/03/25 15:10:00 by ttremel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex.a
CC				=	cc
LIBFT			=	../libft.a
MAKE			=	make --no-print-directory
LIBFT			=	../libft.a
OBJ_PATH		=	./obj
export DEBUG	=	yes

SRCS			=	./pipex.c			\
					./parsing.c			\
					./free.c			\
					./ft_exec.c			\
					./error.c			\
					./ft_wait.c			\
					./process.c

ifeq ($(DEBUG), yes)
	CFLAGS		=	-Wall -Wextra -Werror -g
else
	CFLAGS		=	-Wall -Wextra -Werror
endif

OBJS			=	$(SRCS:%.c=$(OBJ_PATH)/%.o)

$(OBJ_PATH)/%.o: %.c
	@(mkdir -p $(dir $@))
	@($(CC) -o $@ -c $< $(CFLAGS))

$(NAME):	$(OBJS)
	@(ar -rc $(NAME) $(OBJS) $(LIBFT))

all:	$(NAME)

clean:
	@(rm -f $(OBJS))

fclean:	clean
	@(rm -f $(NAME))

re:	fclean all

.PHONY: all bonus clean fclean re