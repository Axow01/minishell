
#ifndef DEFINES_H
# define DEFINES_H

# include "libftms/inc/libft.h"
# include <stdbool.h>

typedef struct s_pipe
{
	int	p_fd[2];
}			t_pipe;

typedef struct s_command
{
	char				**cmd;
	char				*exec_cmd;
	char				**cmd_argv;
	int					stdin_;
	int					stdout_;
	struct s_command	*next;
}		t_command;

typedef struct s_infos
{
	t_command	cmd;
	char		**env;
	char		*pwd;
	char		**path;
	char		*username;
}		t_infos;

typedef enum e_path
{
	ABSOLUTE_PATH = 0,
	COMMAND = 1
}	t_path;

#endif
