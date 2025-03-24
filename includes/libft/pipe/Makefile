# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttremel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/09 16:08:13 by ttremel           #+#    #+#              #
#    Updated: 2025/03/24 14:29:17 by ttremel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex.a
CC				=	cc
LIBFT			=	./libft_utils
MAKE			=	make --no-print-directory
LIBFT			=	../includes/libft/libft.a
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
	CFLAGS	=	-Wall -Wextra -Werror -g
else
	CFLAGS	=	-Wall -Wextra -Werror
endif

OBJS			=	$(SRCS:%.c=$(OBJ_PATH)/%.o)

$(OBJ_PATH)/%.o: %.c
	@($(CC) -o $@ -c $< $(CFLAGS))

all:	$(NAME)

$(NAME):	$(OBJS)
	@(ar -rc $@ $(OBJS) $(LIBFT))

clean:
	@(rm -f $(OBJS))
	@(cd $(LIBFT) && $(MAKE) clean)

fclean:	clean
	@(rm -f $(NAME))
	@(cd $(LIBFT) && $(MAKE) fclean)

re:	fclean all

.PHONY: all bonus clean fclean re