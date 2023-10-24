
#include "../../includes/minishell.h"

char	*cmd_accessible(char **cmd, int modes)
{
	if (!cmd)
		return (NULL);
	if (access(cmd[0], modes) == -1)
		return (NULL);
	return (cmd[0]);
}

t_path	check_path_type(char **cmd)
{
	if (!cmd || !cmd[0] || !cmd[0][0])
		return (0);
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

void	clean_cmd_struct(t_command *cmd)
{
	t_command	*buf;
	t_command	*prev;
	int			i;

	buf = cmd->next;
	i = -1;
	while (cmd->cmd[++i])
		cmd->cmd[i] = mms_free(cmd->cmd[i]);
	cmd->exec_cmd = mms_free(cmd->exec_cmd);
	cmd->next = NULL;
	while (buf)
	{
		i = -1;
		while (buf->cmd && buf->cmd[++i])
			buf->cmd[i] = mms_free(buf->cmd[i]);
		if (buf->stdin_ > 0)
			close(buf->stdin_);
		if (buf->stdout_ > 1)
			close(buf->stdout_);
		buf->exec_cmd = mms_free(buf->exec_cmd);
		buf->cmd_argv = NULL;
		prev = buf;
		buf = buf->next;
		prev = mms_free(prev);
	}
}

bool	execution(t_infos *infos)
{
	t_command	*cmd_buffer;


	if (ft_strncmp(infos->cmd.cmd[0], "exit", 4) == 0)
		mms_kill(NULL, true, 0);
	cmd_buffer = &infos->cmd;
	while (cmd_buffer)
	{
		if (check_path_type(cmd_buffer->cmd) == COMMAND)
			cmd_buffer->exec_cmd = get_cmd_path(cmd_buffer->cmd, infos->path);
		else
			cmd_buffer->exec_cmd = cmd_accessible(cmd_buffer->cmd, R_OK | X_OK);
		cmd_buffer->cmd_argv = cmd_buffer->cmd;
		cmd_buffer = cmd_buffer->next;
	}
	execution_dispach(infos);
	clean_cmd_struct(&infos->cmd);
	return (true);
}
