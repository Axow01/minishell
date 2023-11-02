
#include "../../includes/minishell.h"

/// @brief This initiate the pipes.
/// @param pipes pipe struct.
/// @return true if succes false if not.
bool	init_pipefd(t_command *cmd)
{
	int	ret;

	if (!cmd)
		return (false);
	ret = pipe(cmd->c_pipe);
	if (ret == -1)
		return (false);
	return (true);
}

void	wait_for_programs(t_infos *infos)
{
	t_command	*buf;

	buf = &infos->cmd;
	while (buf)
	{
		buf->pid = waitpid(buf->pid, NULL, 0);
		buf = buf->next;
	}
}
