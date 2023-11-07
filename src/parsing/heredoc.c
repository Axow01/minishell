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
		line = readline(">");
		if (!line)
			return (false);
		mms_add_ptr(line);
		if (ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
			return (false);
		new = heredoc_parsing(line, do_dollar);
		if (!new)
			return (false);
		ft_putendl_fd(new, fd);
	}
	return (true);
}

void heredoc_clean(void)
{
	size_t i;

	i = get_infos();
	while (i >= 0)
	{
		unlink(ft_stringf());
		i--;
	}
	
}

void heredoc(t_command *head)
{
	size_t i;
	int fd;
	char *fnum;
	t_infos *infos;

	i = 0;
	fd = 0;
	infos = get_infos();
	while (head && head->tmp && head->tmp[i])
	{
		if (head->tmp[i][0] && isredirec(head->tmp[i]))
		{
			if (isredirec(head->tmp[i]) == 2 && head->tmp[i][0] == '<')
			{
				fnum = ft_stringf("%s%s%d", "/tmp", "/heredoc", infos->nb_heredoc);
				infos->nb_heredoc++;
				if (head->stdin_ > 2)
					close(fd);
				fd = open(fnum, O_CREAT | O_WRONLY, 0644);
				head->stdin_ = fd;
				fnum = mms_free(fnum);
				if (fd < 0)
					break;
				heredoc_read(head->tmp[i + 1], fd);
			}
		}
		i++;
	}
}