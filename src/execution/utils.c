#include "../../includes/minishell.h"

t_path	check_path_type(char **cmd)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
		return (-1);
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

void	config_builtins_cmd(t_command *cmd_buffer, t_infos *infos)
{
	if (check_for_builtins(cmd_buffer))
	{
		cmd_buffer->is_builtin = true;
		cmd_buffer->exec_cmd = (char *)get_builtin_ptr(cmd_buffer);
	}
	else
		cmd_buffer->exec_cmd = get_cmd_path(cmd_buffer->cmd,
				infos->path);
}

void	builtin_redirections_fd(int in, int out)
{
	static int	std[2] = {0, 0};

	if (in == STDIN_FILENO && out == STDOUT_FILENO)
		return ;
	if (std[0] > 0 || std[1] > 0)
	{
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		std[0] = 0;
		std[1] = 0;
		return ;
	}
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	if (in > STDIN_FILENO)
		dup2(in, STDIN_FILENO);
	if (out > STDOUT_FILENO)
		dup2(out, STDOUT_FILENO);
}

void	path_change_execution(t_command *cmd)
{
	get_infos()->path = path_split(env_to_path(get_infos()->env));
	if (check_path_type(cmd->cmd) == COMMAND && !cmd->is_builtin)
		cmd->exec_cmd = get_cmd_path(cmd->cmd, get_infos()->path);
}
