
#include "../../includes/minishell.h"

static void	change_in_out(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->c_pipe[0] > 0 && cmd->c_pipe[1] > 0 && cmd->stdout_ == STDOUT_FILENO)
		cmd->stdout_ = cmd->c_pipe[1];
	else if (cmd->c_pipe[0] > 0 && cmd->c_pipe[1] > 0)
		close(cmd->c_pipe[1]);
	if (cmd->previous && cmd->previous->c_pipe[0] > 0 && cmd->previous->c_pipe[1] > 0 && cmd->stdin_ == STDIN_FILENO)
		cmd->stdin_ = cmd->previous->c_pipe[0];
	else if (cmd->previous && cmd->previous->c_pipe[0] > 0 && cmd->previous->c_pipe[1] > 0)
		close(cmd->previous->c_pipe[0]);
}

static void	close_unused_fd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->c_pipe[0] > 0)
		close(cmd->c_pipe[0]);
	if (cmd->previous && cmd->previous->c_pipe[1] > 0)
		close(cmd->previous->c_pipe[1]);
}

static void	close_all_pipes(t_command *cmd)
{
	t_command	*buf;

	if (!cmd)
		return ;
	buf = cmd;
	while (buf)
	{
		if (buf->c_pipe[0] > 0)
			close(buf->c_pipe[0]);
		if (buf->c_pipe[1] > 0)
			close(buf->c_pipe[1]);
		buf = buf->next;
	}
}

static void	run_fork(t_command *buf, t_infos *infos)
{
	char	**env;

	ft_setup_signal(CHILD);
	close_unused_fd(buf);
	if (buf->stdin_ < 0 || buf->stdout_ < 0)
	{
		close_all_pipes(&infos->cmd);
		mms_kill(NULL, true, 1);
	}
	if (!check_cmd_valid(buf))
		mms_kill(NULL, true, 127);
	if (buf->stdout_ != STDOUT_FILENO)
		dup2(buf->stdout_, STDOUT_FILENO);
	if (buf->stdin_ != STDIN_FILENO)
		dup2(buf->stdin_, STDIN_FILENO);
	env = infos->env;
	if (buf->is_builtin)
	{
		((Builtin_ptr)buf->exec_cmd)(buf->arg_count, buf->cmd_argv, env);
		mms_kill(NULL, true, 1);
	}
	untrack_cmd(buf);
	rl_clear_history();
	mms_kill(NULL, false, 0);
	mms_kill(NULL, false, execve(buf->exec_cmd, buf->cmd_argv, env));
}


static bool	run_all(t_infos *infos)
{
	t_command	*buf;

	buf = &infos->cmd;
	while (buf)
	{
		if ((buf->c_pipe[0] == 0 || buf->c_pipe[1] == 0) && buf->next)
			init_pipefd(buf);
		change_in_out(buf);
		get_infos()->path = path_split(env_to_path(get_infos()->env));
		if (check_path_type(buf->cmd) == COMMAND && !buf->is_builtin)
			buf->exec_cmd = get_cmd_path(buf->cmd, get_infos()->path);
		buf->pid = fork();
		if (buf->pid == -1)
			write(STDERR_FILENO, "Failled to create forks\n", 25);
		if (buf->pid == 0)
			run_fork(buf, infos);
		if (buf->previous)
		{
			close(buf->previous->c_pipe[0]);
			close(buf->previous->c_pipe[1]);
		}
		buf = buf->next;
	}
	close_all_pipes(&infos->cmd);
	wait_for_programs(infos);
	return (true);
}

bool	execution_pipe(t_infos *infos)
{
	if (!init_pipefd(&infos->cmd))
		mms_kill("Pipe failled to init!\n", true, 2);
	if (!run_all(infos))
		mms_kill("Failed to execute\n", true, 2);
	return (true);
}
