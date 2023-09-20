
#include "../../includes/minishell.h"

bool	cmd_accessible(char **cmd, int modes)
{
	if (access(cmd[0], modes) == -1)
		return (false);
	return (true);
}

/// @brief This function return the type of the path.
//				(absolute or command from the environement).
/// @param cmd The cmd double char pointer.
/// @return The right path type.
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

void	launch_program(char *cmd_absolute, t_infos *infos)
{
	pid_t	pid;
	char	**argv;
	int		*status;

	if (cmd_absolute)
	{
		status = NULL;
		argv = generate_argv(infos->cmd);
		pid = fork();
		if (pid == 0)
			execve(cmd_absolute, argv, infos->env);
		waitpid(pid, status, 0);
		cmd_absolute = mms_free(cmd_absolute);
		argv = mms_free(argv);
	}
	else
		printf("minishell: %s: command not found\n", infos->cmd[0]);
}

bool	execution(t_infos *infos)
{
	if (!infos->cmd || !infos->env)
		return (false);
	if (ft_strncmp(infos->cmd[0], "exit", 4) == 0)
		mms_kill("", true, 0);
	if (check_path_type(infos->cmd) == ABSOLUTE_PATH)
		launch_program(infos->cmd[0], infos);
	else
		launch_program(get_cmd_path(infos->cmd, infos->path), infos);
	return (true);
}
