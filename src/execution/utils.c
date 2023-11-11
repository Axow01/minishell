
#include "../../includes/minishell.h"

t_path	check_path_type(char **cmd)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
		return (-1);
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

void	config_builtins_cmd(t_command *cmd_buffer, t_infos *infos)
{
	if (check_for_builtins(cmd_buffer))
	{
		cmd_buffer->is_builtin = true;
		cmd_buffer->exec_cmd = (char *)get_builtin_ptr(cmd_buffer);
	}
	else
		cmd_buffer->exec_cmd = get_cmd_path(cmd_buffer->cmd,
				infos->path);
}
