#include "minishell.h"

char	*heredoc_parsing(char *line, bool do_dollar)
{
	size_t	i;
	size_t	j;
	char *new;

	new = NULL;
	if (do_dollar)
		new = mms_alloc(ft_strlen(line) + dollars_count(line) + 1, sizeof(char));
	else
		new = mms_alloc(ft_strlen(line) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (do_dollar && line[i] == '$')
			dollars_token_copy(line, new, &i, &j);
		new[j++] = line[i++];
	}
	mms_free(line);
	return (new);
}

bool	heredoc_read(char *delimiter, int fd)
{
	char *line;
	char *new;
	char *del;
	bool do_dollar;

	do_dollar = false;
	del = delimiter;
	if (char_count(delimiter, '"') > 0 || char_count(delimiter, '\'') > 0)
	{
		do_dollar = false;
		del = remove_quote_token(delimiter);
	}
	else 
		do_dollar = true;
	while (true)
	{
		line = readline("heredoc> ");
		if (!line)
			return (false);
		mms_add_ptr(line);
		if (ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
			return (false);
		new = heredoc_parsing(line, do_dollar);
		if (!new)
			return (false);
		ft_putendl_fd(new, fd);
		line = mms_free(line);
		mms_free(new);
	}
	return (true);
}

void heredoc_clean(void)
{
	int i;
	char *fname;

	i = get_infos()->nb_heredoc;
	while (i >= 0)
	{
		fname = ft_stringf("%s%s%d", "/tmp", "/heredoc", i);
		unlink(fname);
		fname = mms_free(fname);
		i--;
	}
}

bool heredoc(t_command *head)
{
	size_t i;
	int fd;
	char *fname;
	t_infos *infos;
	pid_t pid;

	i = 0;
	fd = 0;
	infos = get_infos();
	while (head && head->tmp && head->tmp[i])
	{
		if (head->tmp[i][0] && isredirec(head->tmp[i]))
		{
			if (isredirec(head->tmp[i]) == 2 && head->tmp[i][0] == '<')
			{
				fname = ft_stringf("/tmp/heredoc%d", infos->nb_heredoc);
				infos->nb_heredoc++;
				if (fd > STDIN_FILENO)
					close(fd);
				get_infos()->child = true;
				pid = fork();
				if (pid == -1)
					break ;
				else if (pid == 0)
				{
					ft_setup_signal(HEREDOC);
					fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
					if (fd < 0)
						mms_kill(NULL, true, 1);
					heredoc_read(head->tmp[i + 1], fd);
					close(fd);
					mms_kill(NULL, true, 0);
				}
				waitpid(pid, &get_infos()->latest_error_code, 0);
				if (WEXITSTATUS(get_infos()->latest_error_code) == 28)
				{
					mms_free(fname);
					return (false);
				}
				get_infos()->child = false;
				fd = open(fname, O_RDONLY);
				head->stdin_ = fd;
				fname = mms_free(fname);
			}
		}
		i++;
	}
	return (true);
}