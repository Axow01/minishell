
#include "../../includes/minishell.h"

/// @brief This count the number of commands in the t_command's structure.
/// @param cmd command struct.
/// @return the number of command in it.
int16_t	count_cmd(t_command *cmd)
{
	int			i;
	t_command	*buf;

	buf = cmd;
	i = 0;
	while (buf)
	{
		i++;
		buf = buf->next;
	}
	return (i);
}

bool	check_for_builtins(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		return (true);
	return (false);
}

void	untrack_cmd(t_command *cmd)
{
	int	i;

	i = -1;
	mms_untrack_ptr(cmd->cmd_argv);
	mms_untrack_ptr(cmd->exec_cmd);
	mms_untrack_ptr(cmd);
	mms_untrack_ptr(get_infos()->env);
	while (cmd->cmd_argv[++i])
		mms_untrack_ptr(cmd->cmd_argv[i]);
	i = -1;
	while (get_infos()->env[++i])
		mms_untrack_ptr(get_infos()->env[i]);
}

static void	simple_exec_run_fork(t_command *cmd)
{
	char	**env;

	env = get_infos()->env;
	if (cmd->stdin_ < 0 || cmd->stdout_ < 0)
		mms_kill(NULL, true, 1);
	dup2(cmd->stdin_, STDIN_FILENO);
	dup2(cmd->stdout_, STDOUT_FILENO);
	untrack_cmd(cmd);
	mms_kill(NULL, false, 0);
	clear_history();
	execve(cmd->exec_cmd, cmd->cmd_argv, env);
	exit(1);
}

bool	simple_exec(t_command *cmd)
{
	pid_t	pid_fork;

	if (cmd->is_builtin)
	{
		if ((Builtin_ptr)cmd->exec_cmd)
			((Builtin_ptr)cmd->exec_cmd)(cmd->arg_count, cmd->cmd_argv, get_infos()->env);
		get_infos()->latest_error_code = 1;
		return (true);
	}
	if (!check_cmd_valid(cmd))
		return (false);
	pid_fork = fork();
	if (pid_fork == -1)
		return (false);
	if (pid_fork == 0)
		simple_exec_run_fork(cmd);
	if (cmd->stdout_ < 0)
		close(cmd->stdout_);
	if (cmd->stdin_ < 0)
		close(cmd->stdin_);
	waitpid(pid_fork, (int *)&get_infos()->latest_error_code, 0);
	return (true);
}

void	execution_dispach(t_infos *infos)
{
	infos->nb_cmd = count_cmd(&infos->cmd);
	if (infos->nb_cmd > 1)
		execution_pipe(infos);
	else
		simple_exec(&infos->cmd);
	if (WIFEXITED(infos->latest_error_code))
		infos->latest_error_code = WEXITSTATUS(infos->latest_error_code);
	else if (WIFSIGNALED(infos->latest_error_code))
		infos->latest_error_code = (128 + WTERMSIG(infos->latest_error_code));
}

