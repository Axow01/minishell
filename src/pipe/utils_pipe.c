
#include "../../includes/minishell.h"

/// @brief This initiate the pipes.
/// @param pipes pipe struct.
/// @return true if succes false if not.
bool	init_pipefd(t_pipe *pipes)
{
	int	i;

	i = 0;
	while (i < get_infos()->nb_cmd - 1)
		if (pipe(pipes[i++].p_fd) == -1)
			return (false);
	return (true);
}
