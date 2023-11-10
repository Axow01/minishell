
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <ncurses.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"
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

/// @brief Freed a double pointer.
/// @param ptr the pointer casting in good type.
/// @return a NULL void pointer.
void	**ft_sfree_2d(void **ptr);

/// @brief Configure the signal system.
/// @param type 
void	ft_setup_signal(int type);

#endif
