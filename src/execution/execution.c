
#include "../../includes/minishell.h"

char	*cmd_accessible(char **cmd, int modes)
{
	if (!cmd)
		return (NULL);
	if (access(cmd[0], modes) == -1)
		return (NULL);
	return (cmd[0]);
}

void	clean_cmd_struct(t_command *cmd)
{
	t_command	*buf;
	t_command	*prev;

	buf = cmd->next;
	cmd->cmd = (char **)ft_sfree_2d((void **)cmd->cmd);
	cmd->tmp = (char **)ft_sfree_2d((void **)cmd->tmp);
	cmd->exec_cmd = mms_free(cmd->exec_cmd);
	cmd->next = NULL;
	while (buf)
	{
		cmd->cmd = (char **)ft_sfree_2d((void **)cmd->cmd);
		cmd->tmp = (char **)ft_sfree_2d((void **)cmd->tmp);
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

t_builtin_ptr	get_builtin_ptr(t_command *cmd)
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
		infos->path = path_split(env_to_path(infos->env));
		cmd_buffer->is_builtin = false;
		if (check_path_type(cmd_buffer->cmd) == COMMAND)
			config_builtins_cmd(cmd_buffer, infos);
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
