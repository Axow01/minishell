#--- LIBRARY NAME ---#
NAME = minishell
LIBFT_DIR = includes/libftms/
LIBFT_A = libft.a

#--- COMMAND VARIABLES ---#
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -fd
AR = ar rcs
MK = mkdir -p

#--- COLORS ---#
GREEN	=	\033[1;32m
RED		=	\033[1;31m
RESET 	= 	\033[0m

#--- INCLUDE ---#
INCDIR = includes

#--- FOLDER ---#
SRC_DIR	=	src
EXECUTION_DIR = execution
PARSINGDIR = parsing
PATH_DIR = path
PIPE_DIR = pipe
BUILTINS_DIR = builtins
SRC		= 	main.c errors.c execution/execution.c path/path.c builtins/cd/cd.c pipe/pipe.c execution/dispach.c pipe/utils_pipe.c pipe/pipe_errors.c builtins/export/export.c builtins/export/utils.c \
			parsing/parsing.c parsing/linked_list.c parsing/is.c parsing/tools.c parsing/dollars.c parsing/string.c parsing/git.c parsing/redirection.c parsing/token.c parsing/setup_line.c
VPATH	=	$(SRC_DIR)

#--- OBJECT ---#
OBJDIR  =   obj
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#--- RULES ---#
$(OBJDIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -I. -c $< -o $@
	
all:	submodules libft $(NAME)

submodules:
	@git submodule update --init --recursive
	
${NAME}:	$(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -Lincludes/libmms/ -lmms -lreadline -lncurses -o minishell
	@echo "$(NAME)$(GREEN) sucessefully compiled 📁.$(RESET)"

$(OBJDIR):
	@$(MK) $(OBJDIR) $(OBJDIR)/$(EXECUTION_DIR) $(OBJDIR)/$(PATH_DIR) $(OBJDIR)/$(BUILTINS_DIR) $(OBJDIR)/$(BUILTINS_DIR)/cd $(OBJDIR)/$(PIPE_DIR) $(OBJDIR)/$(BUILTINS_DIR)/export $(OBJDIR)/parsing

libft:
	@$(MAKE) -C $(LIBFT_DIR)

run:	all
	@./$(NAMES)
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)
	@$(RM)r $(OBJDIR)
	
fclean:	clean	
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(NAME)$(GREEN) object files and executable successfully removed 🗑.$(RESET)"

re:	fclean all

leak: all
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --track-origins=yes --suppressions=$(PWD)/supp.txt ./minishell

.PHONY:	all clean fclean re libft leak
