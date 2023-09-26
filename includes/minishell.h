
#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "libftms/inc/libft.h"
# include "execution.h"
# include "defines.h"
# include "builtins.h"
# include "path.h"
# include "parsing.h"
# include "readline/history.h"
# include "readline/readline.h"

t_infos	*get_infos(void);

#endif
