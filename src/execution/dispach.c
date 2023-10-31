
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

void	check_for_builtins(t_infos *infos)
{
	t_command	*cmd;

	cmd = &infos->cmd;
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		infos->env = ft_export(0, cmd->cmd_argv, infos->env);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		mms_kill(NULL, true, 0);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		cd(ft_length_d_char(cmd->cmd), cmd->cmd_argv, infos->env);
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

bool	simple_exec(t_command *cmd)
{
	pid_t	pid_fork;
	char	**env;

	check_for_builtins(get_infos());
	if (!cmd->exec_cmd)
	{
		if (check_path_type(cmd->cmd) == COMMAND)
			ft_printf("minishell: %s: command not found\n", cmd->cmd[0]);
		else
			ft_printf("minishell: %s: No such file or directory\n", cmd->cmd[0]);
		return (false);
	}
	pid_fork = fork();
	if (pid_fork == -1)
		return (false);
	if (pid_fork == 0)
	{
		env = get_infos()->env;
		dup2(cmd->stdin_, STDIN_FILENO);
		dup2(cmd->stdout_, STDOUT_FILENO);
		untrack_cmd(cmd);
		mms_kill(NULL, false, 0);
		execve(cmd->exec_cmd, cmd->cmd_argv, env);
		exit(1);
	}
	waitpid(pid_fork, NULL, 0);
	return (true);
}

void	execution_dispach(t_infos *infos)
{
	infos->nb_cmd = count_cmd(&infos->cmd);
	if (infos->nb_cmd > 1)
		execution_pipe(infos);
	else
		simple_exec(&infos->cmd);
	return ;
}

