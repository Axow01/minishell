
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
		close(pipes[i++].p_fd[1]);
	}
	pipes = mms_free(pipes);
}

void	run_fork(t_command *buf, t_pipe *pipes, t_infos *infos, int i)
{
	if (buf->stdin_ == STDIN_FILENO)
		close(pipes[i].p_fd[0]);
	if (buf->stdout_ == STDOUT_FILENO)
		close(pipes[i].p_fd[1]);
	dup2(buf->stdin_, STDIN_FILENO);
	dup2(buf->stdout_, STDOUT_FILENO);
	close(pipes[i].p_fd[0]);
	close(pipes[i].p_fd[1]);
	execve(buf->exec_cmd, buf->cmd_argv, infos->env);
}

bool	run_all(t_infos *infos, t_pipe *pipes)
{
	t_command	*buf;
	int			i;
	pid_t		pid;

	buf = &infos->cmd;
	i = 0;
	while (buf)
	{
		buf->pid = fork();
		if (buf->pid == -1)
			mms_kill("Fork error!\n", true, 1);
		if (buf->pid != 0)
			printf("CMD: %s in:%d out: %d pid: %d\n", buf->cmd[0], buf->stdin_, buf->stdout_, buf->pid);
		if (buf->pid == 0)// printf("CMD: %s in:%d out: %d\n", buf->cmd[0], buf->stdin_, buf->stdout_);
			run_fork(buf, pipes, infos, i);
		if (buf->stdin_ != STDIN_FILENO && i < infos->nb_cmd - 1)
			close(pipes[i].p_fd[0]);
		if (buf->stdout_ != STDOUT_FILENO && i < infos->nb_cmd - 1)
			close(pipes[i].p_fd[1]);
		printf("CMD: %s executed\n", buf->cmd[0]);
		i++;
		buf = buf->next;
	}
	buf = &infos->cmd;
	while (buf)
	{
		printf("Waiting on %s pid\n", buf->cmd[0]);
		pid = waitpid(0, NULL, 0);
		printf("%s %d finished\n", buf->cmd[0], pid);
		buf = buf->next;
	}
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
	close_all_pipes(pipes, infos->nb_cmd - 1);
	return (true);
}
