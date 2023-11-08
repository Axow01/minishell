
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

bool	indexing_previous_cmd(t_command *cmd)
{
	t_command	*buf;
	t_command	*temp;

	if (!cmd)
		return (false);
	buf = cmd;
	temp = NULL;
	while (buf)
	{
		buf->previous = temp;
		temp = buf;
		buf = buf->next;
	}
	return (true);
}

static Builtin_ptr	get_builtin_ptr(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (&ft_export);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (&cd);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		return (&ft_exit_minishell);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (&ft_pwd);
	else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (&ft_echo);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		return (&ft_env);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (&ft_unset);
	return (NULL);
}

bool	execution(t_infos *infos)
{
	t_command	*cmd_buffer;

	cmd_buffer = &infos->cmd;
	while (cmd_buffer)
	{
		cmd_buffer->is_builtin = false;
		if (check_path_type(cmd_buffer->cmd) == COMMAND)
		{
			if (check_for_builtins(cmd_buffer))
			{
				cmd_buffer->is_builtin = true;
				cmd_buffer->exec_cmd = (char *)get_builtin_ptr(cmd_buffer);
			}
			else
				cmd_buffer->exec_cmd = get_cmd_path(cmd_buffer->cmd, infos->path);
		}
		else
			cmd_buffer->exec_cmd = cmd_accessible(cmd_buffer->cmd, R_OK | X_OK);
		cmd_buffer->cmd_argv = cmd_buffer->cmd;
		cmd_buffer->arg_count = ft_length_d_char(cmd_buffer->cmd_argv);
		cmd_buffer = cmd_buffer->next;
	}
	if (!indexing_previous_cmd(&infos->cmd))
		return (false);
	execution_dispach(infos);
	clean_cmd_struct(&infos->cmd);
	return (true);
}
