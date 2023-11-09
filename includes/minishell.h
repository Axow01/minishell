
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ncurses.h>
# include <fcntl.h>
# include "libftms/inc/libft.h"
# include "execution.h"
# include "defines.h"
# include "builtins.h"
# include "path.h"
# include "pipe.h"
# include "parsing.h"

t_infos	*get_infos(void);

char	*get_username(char **env);

/// @brief This is like printf but for errors, s,d only.
/// @param fmt The string with some modifier like %s %d. 
/// @return The total written bytes.
int		printf_error(int16_t error_code, char *fmt, ...);

#endif
