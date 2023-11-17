#include "../../includes/minishell.h"

bool	check_cmd_valid(t_command *cmd)
{
	if (!cmd)
		return (false);
	if (!cmd->exec_cmd)
	{
		if (check_path_type(cmd->cmd) == COMMAND)
			printf_error(127, "minishell: %s: command not found\n", cmd->cmd[0]);
		else
			printf_error(127, "minishell: %s: no such file or directory\n",
				cmd->cmd[0]);
		return (false);
	}
	return (true);
}
