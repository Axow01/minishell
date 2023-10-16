
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ncurses.h>
# include "libftms/inc/libft.h"
# include "execution.h"
# include "defines.h"
# include "builtins.h"
# include "path.h"
# include "pipe.h"

t_infos	*get_infos(void);

char	*get_username(char **env);

#endif
