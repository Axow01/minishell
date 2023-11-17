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
		buf->pid = waitpid(buf->pid, &infos->latest_error_code, 0);
		buf = buf->next;
	}
	if (WIFEXITED(infos->latest_error_code))
		infos->latest_error_code = WEXITSTATUS(infos->latest_error_code);
	else if (WIFSIGNALED(infos->latest_error_code))
		infos->latest_error_code = (128 + WTERMSIG(infos->latest_error_code));
}

void	change_in_out(t_command *cmd)
{
	if (!cmd)
		return ;
	get_infos()->path = path_split(env_to_path(get_infos()->env));
	if (check_path_type(cmd->cmd) == COMMAND && !cmd->is_builtin)
		cmd->exec_cmd = get_cmd_path(cmd->cmd, get_infos()->path);
	if (cmd->c_pipe[0] > 0 && cmd->c_pipe[1] > 0
		&& cmd->stdout_ == STDOUT_FILENO)
		cmd->stdout_ = cmd->c_pipe[1];
	else if (cmd->c_pipe[0] > 0 && cmd->c_pipe[1] > 0)
		mms_close(cmd->c_pipe[1]);
	if (cmd->previous && cmd->previous->c_pipe[0] > 0
		&& cmd->previous->c_pipe[1] > 0 && cmd->stdin_ == STDIN_FILENO)
		cmd->stdin_ = cmd->previous->c_pipe[0];
	else if (cmd->previous && cmd->previous->c_pipe[0] > 0
		&& cmd->previous->c_pipe[1] > 0)
		mms_close(cmd->previous->c_pipe[0]);
}

void	pipe_fork_verif(t_infos *infos, t_command *buf)
{
	if (buf->stdin_ < 0 || buf->stdout_ < 0)
	{
		close_all_pipes(&infos->cmd);
		mms_kill(NULL, true, 1);
	}
	if (!check_cmd_valid(buf))
	{
		close_all_pipes(&infos->cmd);
		mms_kill(NULL, true, 127);
	}
}
