#--- LIBRARY NAME ---#
NAME = minishell
LIBFT_DIR = includes/libftms/
LIBFT_A = libft.a

#--- COMMAND VARIABLES ---#
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g 
RM = rm -fd
AR = ar rcs
MK = mkdir -p

#--- COLORS ---#
GREEN	=	\033[1;32m
RED		=	\033[1;31m
RESET 	= 	\033[0m

#--- INCLUDE ---#
INCDIR = includes

#--- SOURCE ---#
SRC_DIR	=	src
EXECUTION_DIR = execution
PATH_DIR = path
PIPE_DIR = pipe
BUILTINS_DIR = builtins
SRC		= 	main.c execution/execution.c path/path.c builtins/cd/cd.c pipe/pipe.c execution/dispach.c
VPATH	=	$(SRC_DIR)
HISTORYLIB    =    readline/libhistory.a
READLINELIB    =    readline/libreadline.a

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
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -Lincludes/libmms/ -lmms -lreadline -lhistory -lncurses -o minishell
	@echo "$(NAME)$(GREEN) sucessefully compiled 📁.$(RESET)"

$(OBJDIR):
	@$(MK) $(OBJDIR) $(OBJDIR)/$(EXECUTION_DIR) $(OBJDIR)/$(PATH_DIR) $(OBJDIR)/$(BUILTINS_DIR) $(OBJDIR)/$(BUILTINS_DIR)/cd $(OBJDIR)/$(PIPE_DIR)

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

.PHONY:	all clean fclean re libft
