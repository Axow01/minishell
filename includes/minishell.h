
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline.h>
# include <history.h>
# include "libftms/inc/libft.h"
# include "execution.h"
# include "defines.h"
# include "builtins.h"
# include "path.h"
# include "pipe.h"

t_infos	*get_infos(void);

char	*get_username(char **env);

echo allhello | cat

#endif
