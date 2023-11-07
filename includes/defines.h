
#ifndef DEFINES_H
# define DEFINES_H

# include "libftms/inc/libft.h"
# include <stdbool.h>

typedef void	(*Builtin_ptr)(int, char **, char **);

typedef struct s_command
{
	char				**cmd;
	char				**tmp;
	pid_t				pid;
	char				*exec_cmd;
	char				**cmd_argv;
	int					c_pipe[2];
	int8_t				arg_count;
	int					stdin_;
	int					stdout_;
	bool				is_builtin;
	struct s_command	*previous;
	struct s_command	*next;
}		t_command;

typedef struct s_infos
{
	t_command		cmd;
	int8_t			nb_cmd;
	char			**env;
	char			*pwd;
	char			**path;
	char			*username;
	int				latest_error_code;
}		t_infos;

typedef enum e_path
{
	ABSOLUTE_PATH = 0,
	COMMAND = 1
}	t_path;

#endif
