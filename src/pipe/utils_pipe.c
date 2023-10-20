
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

void	close_all_except(t_pipe *pipes, int read, int writes)
{
	int	i;

	i = 0;
	while (i <= get_infos()->nb_cmd - 1)
	{
		if (pipes[i].p_fd[0] != read && pipes[i].p_fd[0] > 0)
			close(pipes[i].p_fd[0]);
		if (pipes[i].p_fd[1] != writes && pipes[i].p_fd[1] > 0)
			close(pipes[i].p_fd[1]);
		i++;
	}
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

void	check_pipes_in_out(t_command *cmd, t_pipe *pipes, int index)
{
	if (cmd->stdin_ != STDIN_FILENO)
	{
		if (index != 0)
			close(pipes[index - 1].p_fd[0]);
	}
	else
		if (index != 0)
			cmd->stdin_ = pipes[index - 1].p_fd[0];
	if (cmd->stdout_ != STDOUT_FILENO)
	{
		if (index < get_infos()->nb_cmd - 1)
			close(pipes[index].p_fd[1]);
	}
	else
		if (index < get_infos()->nb_cmd - 1)
			cmd->stdout_ = pipes[index].p_fd[1];
}
