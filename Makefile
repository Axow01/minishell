#--- LIBRARY NAME ---#
NAME = minishell
LIBFT_DIR = includes/libftms/
LIBFT_A = libft.a

#--- COMMAND VARIABLES ---#
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g 
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
READ_PATH	= includes/readline
BUILTINS_DIR = builtins
LIBRLINE	= readline-8.2

#--- SOURCE ---#
SRC		= 	main.c execution/execution.c path/path.c builtins/cd/cd.c parsing/ft_strtok.c parsing/parsing.c
VPATH	=	$(SRC_DIR)
HISTORYLIB    =    readline/libhistory.a
READLINELIB    =    readline/libreadline.a

#--- OBJECT ---#
OBJDIR  =   obj
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#--- RULES ---#
$(OBJDIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -I. -c $< -o $@
	
all:	submodules libft readline $(NAME) 

readline	:
	@if [ ! -f ./includes/readline/libreadline.a ]; then \
    	curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz; \
		mkdir -p $(READ_PATH); \
    	tar -xf $(LIBRLINE).tar.gz; \
        rm -rf $(LIBRLINE).tar.gz; \
        cd $(LIBRLINE) && bash configure && make; \
        mv ./libreadline.a ../libs/readline; \
        rm -rf ../$(LIBRLINE); \
        echo "\n----- $(GREEN)Readline $(RESET) succesfully configured ✅ -----\n"; \
    fi

submodules:
	@git submodule update --init --recursive
	
${NAME}:	$(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -Lincludes/libmms/ -lmms -L$(INCDIR)/readline/ -lreadlinemac -lhistorymac -lncurses -o minishell
	@echo "$(NAME)$(GREEN) sucessefully compiled 📁.$(RESET)"

$(OBJDIR):
	@$(MK) $(OBJDIR) $(OBJDIR)/$(EXECUTION_DIR) $(OBJDIR)/$(PATH_DIR) $(OBJDIR)/$(BUILTINS_DIR) $(OBJDIR)/$(BUILTINS_DIR)/cd $(OBJDIR)/$(PARSINGDIR)
	
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
