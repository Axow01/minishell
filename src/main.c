
#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>

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
	t_command	*buf;

	buf = &infos->cmd;
	command = mms_alloc(1, sizeof(t_command));
	command->cmd = ft_split(cmd, ' ');
	command->stdin_ = stdin_;
	command->stdout_ = stdout_;
	command->next = NULL;
	while (buf->next)
		buf = buf->next;
	buf->next = command;
}

bool	read_line(void)
{
	char	*str;
	char	*line;
	t_infos	*infos;
	size_t	count;

	count = 0;
	infos = get_infos();
	if (infos->pwd)
		infos->pwd = mms_free(get_infos()->pwd);
	infos->username = check_for_key("USER", get_infos()->env, 4);
	infos->pwd = check_for_key("PWD", get_infos()->env, 3);
	infos->git_branch = get_branch(&count);
	str = draw_prompt(count);
	line = readline(str);
	str = mms_free(str);
	if (!line)
		return (false);
	mms_add_ptr(line);
	if (*line)
		add_history(line);
	parsing(line);
	line = mms_free(line);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_infos	*infos;
	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	mms_set_alloc_fn(ft_calloc);
	infos = get_infos();
	infos->env = env;
	if (!infos->env)
		mms_kill("minishell: could not retreive env\n", true, 1);
	infos->path = path_split(env_to_path(infos->env));
	ft_setup_signal(PARENT);
	while (1)
	{
		if (!read_line())
			break ;
	}
	mms_kill("", false, 0);
	return (0);
}
