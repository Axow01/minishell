
#include "../../includes/minishell.h"

bool	cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}

bool	execution(t_infos *infos)
{
	int	i;

	if (!infos->cmd || !infos->env)
		return (false);
	i = 0;
	while (infos->cmd[i][0] != 0)
		printf("%s\n", infos->cmd[i++]);
	return (true);
}
