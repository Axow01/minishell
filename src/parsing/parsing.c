#include "minishell.h"
#include <stdio.h>
#include <string.h>

int	count_cmd_total(char *str, char delim)
{
	int	count;
	int	i;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == delim)
			{
				count++;
			}
		}
		i++;
	}
	return (count);
}

static bool	error_cmd_maker(t_command *head)
{
	if (!head->tmp || !head->tmp[0] || !head->tmp[0][0])
	{
		get_infos()->latest_error_code = 258;
		return (printf("%s`|'\n", ERROR_BASE_MSG), false);
	}
	if (!check_valid_redirec(head))
		return (false);
	fd_maker(head);
	if (!heredoc(head))
		return (false);
	tmp_to_cmd(head);
	remove_quote(head);
	return (true);
}

bool	cmd_maker(char *str, size_t len)
{
	size_t		i;
	size_t		end;
	size_t		start;
	t_command	*head;

	i = 0;
	start = 0;
	head = &get_infos()->cmd;
	while (i <= len)
	{
		if ((str[i] == '|' && !isinquote(str, i, QUOTES)) || i == len)
		{
			end = i;
			head->tmp = mms_alloc(ctoken(str, start, end) + 1, sizeof(char *));
			head->stdin_ = STDIN_FILENO;
			head->stdout_ = STDOUT_FILENO;
			get_token(str, start, end, head);
			if (!error_cmd_maker(head))
				return (false);
			head = head->next;
			start = end + 1;
		}
		i++;
	}
	return (true);
}

void	parsing(char *line)
{
	char	*new;
	size_t	len;

	if (char_count(line, ' ') == ft_strlen(line))
	{
		clean_cmd_struct(&get_infos()->cmd);
		return ;
	}
	new = setup_line(line, &len);
	if (new == NULL)
		return ;
	init_cmd_struct(line);
	replace_space(new, 0, len);
	if (isinquote(line, ft_strlen(line) - 1, QUOTES))
		printf("%s(\"or')\n", ERROR_QUOTE_MSG);
	else if (cmd_maker(new, len))
	{
		get_infos()->child = true;
		execution(get_infos());
		get_infos()->child = false;
	}
	clean_cmd_struct(&get_infos()->cmd);
	heredoc_clean();
	new = mms_free(new);
}
