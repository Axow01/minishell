
#include "../../includes/minishell.h"

bool cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}
