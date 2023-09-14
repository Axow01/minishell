
#include "../../includes/minishell.h"

bool	cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}

t_path	check_path_type(char **cmd)
{
	if (cmd[0][0] == '.' || cmd[0][0] == '/')
		return (ABSOLUTE_PATH);
	return (COMMAND);
}

char	**generate_argv(char **cmd)
{
	char	**argv;
	int		nb_args;
	int		i;

	nb_args = 2;
	i = 0;
	while (cmd[++i])
		nb_args++;
	argv = mms_alloc(nb_args, sizeof(char **));
	i = -1;
	while (cmd[++i])
		argv[i] = cmd[i];
	argv[i] = 0;
	return (argv);
}

bool	execution(t_infos *infos)
{
	pid_t	pid;
	char	**argv;
	char	*temp_cmd;
	int		*status;

	if (!infos->cmd || !infos->env)
		return (false);
	if (ft_strncmp(infos->cmd[0], "exit", 4) == 0)
		mms_kill("", true, 0);
	temp_cmd = get_cmd_path(infos->cmd, infos->path);
	status = NULL;
	execve(infos->cmd[0], );
	mms_kill();
	if (temp_cmd)
	{
		infos->cmd[0] = mms_free(infos->cmd[0]);
		infos->cmd[0] = temp_cmd;
		argv = generate_argv(infos->cmd);
		pid = fork();
		if (pid == 0)
		{
			execve(infos->cmd[0], argv, infos->env);
			mms_kill(NULL, true, 0);
		}
		waitpid(pid, status, 0);
		argv = mms_free(argv);
	}
	else
		printf("minishell: %s: command not found\n", infos->cmd[0]);
	return (true);
}
