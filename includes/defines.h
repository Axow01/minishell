
#ifndef DEFINES_H
# define DEFINES_H

# include "libftms/inc/libft.h"
# include <stdbool.h>

typedef struct s_infos
{
	char	**cmd;
	char	**env;
	char	**path;
}		t_infos;

typedef enum e_path
{
	ABSOLUTE_PATH = 0,
	COMMAND = 1
}	t_path;

#endif
