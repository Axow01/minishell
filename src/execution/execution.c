
#include "../../includes/minishell.h"

bool	cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}

/// @brief This function return the type of the path.
//				(absolute or command from the environement).
/// @param cmd The cmd double char pointer.
/// @return The right path type.
t_path	check_path_type(char **cmd)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

char	**generate_argv(char **cmd)
{
	char	**argv;
	int		nb_args;
	int		i;

	nb_args = 2;
	i = 0;
	while (cmd[++i])
		nb_args++;
	argv = mms_alloc(nb_args, sizeof(char **));
	i = -1;
	while (cmd[++i])
		argv[i] = cmd[i];
	argv[i] = 0;
	return (argv);
}

bool	execution(t_infos *infos)
{
	t_command	*cmd_buffer;

	cmd_buffer = &infos->cmd;
	while (cmd_buffer)
	{
		if (check_path_type(cmd_buffer->cmd) == COMMAND)
			cmd_buffer->exec_cmd = get_cmd_path(cmd_buffer->cmd, infos->path);
		else
			cmd_buffer->exec_cmd = cmd_buffer->cmd[0];
		cmd_buffer->cmd_argv = cmd_buffer->cmd;
		cmd_buffer = cmd_buffer->next;
	}
	return (true);
}
