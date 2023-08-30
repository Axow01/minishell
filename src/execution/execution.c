
#include "../../includes/minishell.h"

bool	cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}

t_path	check_path_type(char **cmd)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

bool	execution(t_infos *infos)
{
	if (!infos->cmd || !infos->env)
		return (false);
	return (true);
}
