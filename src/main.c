
#include "../includes/minishell.h"

t_infos	*get_infos(void)
{
	static t_infos	*infos;

	if (!infos)
	{
		infos = mms_alloc(1, sizeof(t_infos));
		infos->env = NULL;
	}
	return (infos);
}

void	add_cmd(char *cmd, int stdin_, int stdout_, t_infos *infos)
{
	t_command	*command;

	command = mms_alloc(1, sizeof(t_command));
	command->cmd = ft_split(cmd, ' ');
	command->stdin_ = stdin_;
	command->stdout_ = stdout_;
	command->next = NULL;
	infos->cmd.next = command;
}

bool	read_line_debug(void)
{
	char	*line;
	char	**cmd;

	if (get_infos()->pwd)
		get_infos()->pwd = mms_free(get_infos()->pwd);
	get_infos()->pwd = get_pwd(get_infos()->env);
	printf("\x1b[36;49;1;3m");
	line = readline(get_infos()->pwd);
	if (!line)
		return (false);
	mms_add_ptr(line);
	add_history(line);
	cmd = ft_split(line, ' ');
	get_infos()->cmd.cmd = cmd;
	get_infos()->cmd.stdout_ = 1;
	// add_cmd("wc -l", STDIN_FILENO, STDOUT_FILENO, get_infos());
	line = mms_free(line);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_infos	*infos;

	(void)argc;
	(void) argv;
	mms_set_alloc_fn(ft_calloc);
	printf("pid: %d\n", getpid());
	infos = get_infos();
	infos->env = env;
	if (!infos->env)
		mms_kill("minishell: could not retreive env\n", true, 1);
	infos->path = path_split(env_to_path(infos->env));
	infos->username = get_username(env);
	while (1)
	{
		if (read_line_debug())
			execution(get_infos());
		else
		{
			mms_kill("REadline failled!\n", true, 1);
		}
	}
	mms_kill("", false, 0);
	return (0);
}
