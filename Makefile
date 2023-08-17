#--- LIBRARY NAME ---#
NAME = minishell
LIBFT_DIR = includes/libftms/
LIBFT_A = libft.a

#--- COMMAND VARIABLES ---#
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
RM = rm -f
AR = ar rcs
MK = mkdir -p

#--- COLORS ---#
GREEN	=	\033[1;32m
RED		=	\033[1;31m
RESET 	= 	\033[0m

#--- INCLUDE ---#
INCDIR = inc

#--- SOURCE ---#
SRCDIR	=	src
SRC		= 	main.c
VPATH	=	$(SRCDIR)

#--- OBJECT ---#
OBJDIR  =   obj
OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#--- RULES ---#
$(OBJDIR)/%.o:	%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -I. -c $< -o $@
	
all:	libft $(NAME)
	
${NAME}:	$(OBJDIR) $(OBJ)
	@$(CC) $(CFLAGS) -I$(INCDIR) -o $(NAME) $(LIBFT_DIR)$(LIBFT_A) $(OBJ) 
	@echo "$(NAME)$(GREEN) sucessefully compiled 📁.$(RESET)"

$(OBJDIR):
	@$(MK) $(OBJDIR)
	
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