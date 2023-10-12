
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
	if (!cmd[0] || !cmd[0][0])
		return (0);
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

bool	execution(t_infos *infos)
{
	t_command	*cmd_buffer;

	if (ft_strncmp(infos->cmd.cmd[0], "exit", 4) == 0)
		mms_kill(NULL, true, 0);
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
	execution_dispach(infos);
	return (true);
}
