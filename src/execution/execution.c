
#include "../../includes/minishell.h"

bool	cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}

t_path	check_path_type(char **cmd)
{
	if (cmd[1][0] == '.' || cmd[1][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

bool	execution(t_infos *infos)
{
	if (!infos->cmd || !infos->env)
		return (false);
	printf("%d\n", check_path_type(infos->cmd));
	return (true);
}
