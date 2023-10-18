
#include "../../includes/minishell.h"

void	change_in_out(t_infos *infos, t_pipe *pipes)
{
	t_command	*bufc;
	int			index;
	int			p_index;

	index = 0;
	p_index = 0;
	bufc = &infos->cmd;
	while (bufc)
	{
		if (index == 0)
			bufc->stdout_ = pipes[p_index].p_fd[1];
		else
		{
			p_index++;
			bufc->stdin_ = pipes[p_index - 1].p_fd[0];
			if (p_index >= infos->nb_cmd - 1)
				break ;
			bufc->stdout_ = pipes[p_index].p_fd[1];
		}
		index++;
		bufc = bufc->next;
	}
}

void	close_all_pipes(t_pipe *pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipes[i].p_fd[0]);
		close(pipes[i].p_fd[1]);
		i++;
	}
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

void	run_fork(t_command *buf, t_pipe *pipes, t_infos *infos, int i)
{
	(void)i;
	close_all_except(pipes, buf->stdin_, buf->stdout_);
	if (STDIN_FILENO != buf->stdin_)
		dup2(buf->stdin_, STDIN_FILENO);
	if (STDOUT_FILENO != buf->stdout_)
		dup2(buf->stdout_, STDOUT_FILENO);
	printf("ErrorCode: %d\n", execve(buf->exec_cmd, buf->cmd_argv, infos->env));
}

bool	run_all(t_infos *infos, t_pipe *pipes)
{
	t_command	*buf;
	int			i;

	buf = &infos->cmd;
	i = 0;
	while (buf)
	{
		buf->pid = fork();
		if (buf->pid == -1)
			mms_kill("Fork error!\n", true, 1);
		if (buf->pid == 0)
			run_fork(buf, pipes, infos, i);
		i++;
		buf = buf->next;
	}
	close_all_pipes(pipes, infos->nb_cmd - 1);
	wait_for_programs(pipes, infos);
	return (true);
}

bool	execution_pipe(t_infos *infos)
{
	t_pipe	*pipes;

	pipes = mms_alloc(infos->nb_cmd, sizeof(t_pipe));
	if (!init_pipefd(pipes))
		mms_kill("Pipe failled to init!\n", true, 2);
	change_in_out(infos, pipes);
	if (!run_all(infos, pipes))
		mms_kill("Failed to execute\n", true, 2);
	mms_free(pipes);
	return (true);
}
