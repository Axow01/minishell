
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

void	close_sp_pid(t_infos *infos, pid_t pid)
{
	t_command	*buf;

	buf = &infos->cmd;
	while (buf)
	{
		if (buf->pid == pid)
		{
			if (buf->stdout_ != STDOUT_FILENO)
				close(buf->stdout_);
			printf("CMD: %s PID: %d\n", buf->cmd[0], buf->pid);
			return ;
		}
		buf = buf->next;
	}
}

void	wait_for_programs(t_pipe *pipes, t_infos *infos)
{
	t_command	*buf;

	buf = &infos->cmd;
	(void)pipes;
	while (buf)
	{
		buf->pid = waitpid(buf->pid, NULL, 0);
		buf = buf->next;
	}
}
