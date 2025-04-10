# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttremel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/09 11:52:19 by ttremel           #+#    #+#              #
#    Updated: 2025/04/10 18:50:17 by ttremel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	cc
GNL			=	./get_next_line
PRINTF		=	./printf
OBJ_PATH	=	./obj

SRCS		=	ft_atoi.c						\
				ft_atol.c						\
				ft_atoll.c						\
				ft_ato128.c						\
				ft_calloc.c						\
				ft_isalnum.c					\
				ft_isalpha.c					\
				ft_isascii.c					\
				ft_isdigit.c					\
				ft_isprint.c					\
				ft_memcpy.c						\
				ft_strdup.c						\
				ft_strlen.c						\
				ft_memmove.c					\
				ft_memset.c						\
				ft_bzero.c						\
				ft_strlcpy.c					\
				ft_strlcat.c					\
				ft_tolower.c					\
				ft_toupper.c					\
				ft_strchr.c						\
				ft_strrchr.c					\
				ft_strncmp.c					\
				ft_strnstr.c					\
				ft_memchr.c						\
				ft_memcmp.c						\
				ft_itoa.c						\
				ft_putchar_fd.c					\
				ft_putstr_fd.c					\
				ft_putendl_fd.c					\
				ft_putnbr_fd.c					\
				ft_strjoin.c					\
				ft_split.c						\
				ft_strtrim.c					\
				ft_strmapi.c					\
				ft_striteri.c					\
				ft_substr.c						\
				ft_join.c						\
				ft_strcat.c						\
				ft_strncat.c					\
				ft_strndup.c					\
				ft_memdup.c						\
				ft_abs.c						\
				ft_strcmp.c						\
				ft_lstadd_back.c				\
				ft_lstadd_front.c				\
				ft_lstclear.c					\
				ft_lstdelone.c					\
				ft_lstiter.c					\
				ft_lstlast.c					\
				ft_lstmap.c						\
				ft_lstnew.c						\
				ft_lstsize.c					\
				ft_random.c						\
				$(PRINTF)/ft_args.c				\
				$(PRINTF)/ft_printf.c			\
				$(PRINTF)/ft_num_count.c		\
				$(PRINTF)/ft_putaddress_fd.c	\
				$(PRINTF)/ft_putbaseuint_fd.c	\
				$(PRINTF)/ft_putuint_fd.c		\
				$(PRINTF)/ft_sizeaddress.c		\
				$(PRINTF)/ft_strlenf.c			\
				$(PRINTF)/ft_ubase_count.c		\
				$(PRINTF)/ft_uint_count.c		\
				$(PRINTF)/print_putstr_fd.c		\
				$(GNL)/get_next_line.c			\
				$(GNL)/get_next_line_utils.c

ifeq ($(DEBUG), yes)
	CFLAGS	=	-Wall -Wextra -Werror -g
else
	CFLAGS	=	-Wall -Wextra -Werror -g
endif

OBJS		=	$(SRCS:%.c=$(OBJ_PATH)/%.o)

all: $(NAME) gnl printf

$(OBJ_PATH)/%.o: %.c
	@(mkdir -p $(dir $@))
	@($(CC) -o $@ -c $< $(CFLAGS) )

$(NAME): $(OBJS)
	@(ar -rc $(NAME) $(OBJS))

gnl:
	@(cd $(GNL) && $(MAKE))

printf:
	@(cd $(PRINTF) && $(MAKE))

clean:
	@(rm -f $(OBJS))
	@(cd $(PRINTF) && $(MAKE) clean)
	@(cd $(GNL) && $(MAKE) clean)

fclean: clean
	@(rm -f $(NAME))
	@(cd $(PRINTF) && $(MAKE) fclean)
	@(cd $(GNL) && $(MAKE) fclean)

re: fclean all

.PHONY: gnl printf all bonus clean fclean re
