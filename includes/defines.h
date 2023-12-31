#ifndef DEFINES_H
# define DEFINES_H

# include "libftms/inc/libft.h"
# include <stdbool.h>

typedef void	(*t_builtin_ptr)(int, char **, char **);

typedef enum e_type
{
	CHILD,
	PARENT,
	HEREDOC
}						t_type;

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
}						t_command;

typedef struct s_infos
{
	t_command			cmd;
	int8_t				nb_cmd;
	int					nb_heredoc;
	bool				child;
	char				**env;
	char				*pwd;
	char				**path;
	char				*username;
	char				*git_branch;
	int					latest_error_code;
}						t_infos;

typedef enum e_path
{
	ABSOLUTE_PATH = 0,
	COMMAND = 1
}						t_path;

#endif
