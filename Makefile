MAKEFLAGS+=	--no-print-directory

NAME= minishell

MY_SOURCES= sources/main.c \

MY_SOURCES+=sources/parsing/parsing.c \
			sources/parsing/token.c \
			sources/parsing/get_path.c \
			sources/parsing/token_command.c \
			sources/parsing/string_parsing.c \
			sources/parsing/token_operator.c \
			sources/parsing/token_redirection.c \

MY_SOURCES+=sources/command_handling/create_command.c \
			sources/command_handling/create_redirection.c \
			sources/command_handling/get_command.c \
			sources/command_handling/typing.c \

MY_SOURCES+=sources/execution/close.c \
			sources/execution/ft_exec.c \
			sources/execution/ft_pipe.c \
			sources/execution/ft_wait.c \
			sources/execution/open_fd.c \
			sources/execution/redirect.c \

MY_SOURCES+=sources/built-ins/ft_cd.c \
			sources/built-ins/ft_echo.c \
			sources/built-ins/ft_env.c \
			sources/built-ins/ft_export.c \
			sources/built-ins/ft_pwd.c \
			sources/built-ins/ft_unset.c \
			sources/built-ins/ft_exit.c \

MY_SOURCES+=sources/error_handling/error_command.c \
			sources/error_handling/error_parsing.c \
			sources/error_handling/error.c \

MY_SOURCES+=utils/utils.c \
			utils/history.c \
			utils/free.c \
			utils/signals.c \
			

MY_OBJECTS_PATH	= ./.obj
MY_OBJECTS = $(MY_SOURCES:%.c=$(MY_OBJECTS_PATH)/%.o)

# ====================
#      COMMANDS
# ====================

RM					=	rm -f
CC					=	cc -g
export DEBUG		=	yes

ifeq ($(DEBUG), yes)
	STANDARD_FLAGS	=	-Wall -Wextra -Werror -g
else
	STANDARD_FLAGS	=	-Wall -Wextra -Werror
endif

# ====================
#    LIBFT SETTINGS
# ====================

LIBFT_DIR			=	includes/libft
LIBFT				=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES		=	-I$(LIBFT_DIR)

# ====================
#  READLINE SETTINGS
# ====================

READLINE_FLAGS		=	-lreadline -lhistory
READLINE_INCLUDES	=	-I/usr/include/readline

# ====================
#        HEADER
# ====================

define HEADER
	$(CYAN) _____     __     ______     ______     __    __
	$(CYAN)/\  __-.  /\ \   /\  == \   /\  ___\   /\ "-./  \\
	$(CYAN)\ \ \/\ \ \ \ \  \ \  __<   \ \  __\   \ \ \-./\ \\
	$(CYAN) \ \____-  \ \_\  \ \_\ \_\  \ \_____\  \ \_\ \ \_\\
	$(CYAN)  \/____/   \/_/   \/_/ /_/   \/_____/   \/_/  \/_/\
	$(CYAN)

endef
export HEADER

# ====================
#     AINSI COLORS
# ====================

RESET			=	\033[0m
GREEN			=	\033[0;32m
CYAN			=	\033[0;36m
BLUE			=	\033[0;34m
YELLOW			=	\033[0;33m
RED				=	\033[0;31m

# ====================
#     COMPILATION
# ====================

all: $(NAME)

$(MY_OBJECTS_PATH)/%.o: %.c
	@clear
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) -o $@ -c $< $(STANDARD_FLAGS) $(READLINE_INCLUDES)
	@$(eval COMPILED_FILES += "$< $(GREEN)🗹\n$(RESET)")
	@clear
	@echo "\n$$HEADER"

$(LIBFT):
	@make --directory $(LIBFT_DIR)

$(NAME): $(LIBFT) $(MY_OBJECTS)
	@$(CC) $(STANDARD_FLAGS) $(READLINE_FLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFT)
	@echo "\n$(GREEN)All files have been successfully compiled!$(RESET)"
	@echo "$(CYAN)Compiled files:$(RESET)"
	@echo " "$(COMPILED_FILES)

clean:
	@$(RM) $(LIBFT) $(MY_OBJECTS)
	@make clean --directory  $(LIBFT_DIR)
	@clear
	@echo "\n$(CYAN)   ╔════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)     All objects have been deleted! $(RESET)"
	@echo "$(CYAN)   ╚════════════════════════════════╝$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean --directory  $(LIBFT_DIR)
	@clear
	@echo "\n$(CYAN)   ╔════════════════════════════════════════╗$(RESET)"
	@echo "$(CYAN)      All cleaned up! Ready to build fresh! $(RESET)"
	@echo "$(CYAN)   ╚════════════════════════════════════════╝$(RESET)"

re: fclean all

.PHONY: all clean fclean re
