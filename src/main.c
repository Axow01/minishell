
#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>

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

bool	read_line_debug(void)
{
	char	*line;

	// char	**cmd;
	if (get_infos()->pwd)
		get_infos()->pwd = mms_free(get_infos()->pwd);
	get_infos()->username = get_username(get_infos()->env);
	get_infos()->pwd = get_pwd(get_infos()->env);
	printf("\x1b[36;49;1;3m");
	line = readline(get_infos()->pwd);
	if (!line)
		return (false);
	mms_add_ptr(line);
	add_history(line);
	parsing(line);
	line = mms_free(line);
	return (true);
}

char	*get_branch(void)
{
	char	*git_dir;
	char	*new;
	char	*temp;
	int		fd;
	size_t	i;

	fd = 0;
	git_dir = ft_strdup(".git/HEAD");
	while (access(git_dir, F_OK) != 0 && char_count(git_dir,
			'/') < char_count(get_infos()->pwd, '/'))
		git_dir = ft_stringf("%s%s", "../", git_dir);
	if (access(git_dir, F_OK) == 0)
	{
		fd = open(git_dir, O_RDONLY);
		temp = get_next_line(fd);
		i = ft_strlen(temp) - 1;
		while (temp[i] && temp[i] != '/')
			i--;
		new = ft_del_char(ft_strdup(&temp[i + 1]), '\n');
		mms_free(temp);
		mms_free(git_dir);
		close(fd);
		return (new);
	}
	return (NULL);
}

bool	read_line(void)
{
	char	*str;
	char	*line;
	t_infos	*infos;

	infos = get_infos();
	if (infos->pwd)
		infos->pwd = mms_free(get_infos()->pwd);
	infos->username = check_for_key("USER", get_infos()->env, 4);
	infos->pwd = check_for_key("PWD", get_infos()->env, 3);
	infos->git_branch = get_branch();
	str = ft_stringf("\x1b[36;49;1;3m%s \x1b[34mgit:\x1b[31m() \x1b[32;1m%s\x1b[38;5;249m > ", infos->pwd, infos->username);
	line = readline(str);
	if (!line)
		return (false);
	mms_add_ptr(line);
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
	mms_set_alloc_fn(ft_calloc);
	infos = get_infos();
	infos->env = env;
	if (!infos->env)
		mms_kill("minishell: could not retreive env\n", true, 1);
	infos->path = path_split(env_to_path(infos->env));
	while (1)
	{
		if (!read_line())
			break ;
	}
	mms_kill("", false, 0);
	return (0);
}
