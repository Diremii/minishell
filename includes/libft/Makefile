NAME=libft.a

MY_SOURCES=ft_atoi.c ft_isdigit.c ft_memmove.c ft_split.c ft_strlcpy.c \
            ft_strtrim.c ft_bzero.c ft_isprint.c ft_memset.c ft_strchr.c \
            ft_strlen.c ft_substr.c ft_calloc.c ft_itoa.c ft_putchar_fd.c \
            ft_strdup.c ft_strmapi.c ft_tolower.c ft_isalnum.c ft_memchr.c \
            ft_putendl_fd.c ft_striteri.c ft_strncmp.c ft_toupper.c \
            ft_isalpha.c ft_memcmp.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c \
            ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c \
			ft_strcmp.c get_next_line.c get_next_line_utils.c \

BONUS= ft_lstnew_bonus.c \
       ft_lstadd_front_bonus.c \
       ft_lstsize_bonus.c \
       ft_lstlast_bonus.c \
       ft_lstadd_back_bonus.c \
       ft_lstdelone_bonus.c \
       ft_lstclear_bonus.c \
       ft_lstiter_bonus.c \
       ft_lstmap_bonus.c

ALL_SOURCES=$(MY_SOURCES) $(BONUS)

MY_OBJECTS=$(ALL_SOURCES:.c=.o)

RM=rm -f

CC=cc
ARRC=ar -rcs
FLAGS=-Wall -Werror -Wextra -g

RESET=\033[0m
GREEN=\033[0;32m
CYAN=\033[0;36m
BLUE=\033[0;34m
YELLOW=\033[0;33m
RED=\033[0;31m

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@$(ARRC) $(NAME) $(MY_OBJECTS)

bonus: $(BONUS:.c=.o)
	@$(ARRC) $(NAME) $^

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@
	@clear

clean:
	@$(RM) $(MY_OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
