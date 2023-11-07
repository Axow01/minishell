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

void	tmp_to_cmd(t_command *head)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	head->cmd = mms_alloc(count_nonerdt_token(head->tmp) + 1,
		sizeof(char *));
	while (head->tmp && head->tmp[i])
	{
		if (isredirec(head->tmp[i]))
			i++;
		else
			head->cmd[j++] = head->tmp[i];
		i++;
	}
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
			head->tmp = mms_alloc(count_token(str, start, end) + 1,
					sizeof(char *));
			head->stdin_ = STDIN_FILENO;
			head->stdout_ = STDOUT_FILENO;
			get_token(str, start, end, head);
			if (!head->tmp || !head->tmp[0] || !head->tmp[0][0])
				return (printf("%s`|'\n", ERROR_BASE_MSG), false);
			if (!check_valid_redirec(head))
				return (false);
			fd_maker(head);
			remove_quote(head);
			tmp_to_cmd(head);
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

	new = setup_line(line, &len);
	if (new == NULL)
		return ;
	init_cmd_struct(line);
	replace_space(new, 0, len);
	if (isinquote(line, ft_strlen(line) - 1, QUOTES))
		printf("%s(\"or')\n", ERROR_QUOTE_MSG);
	else if (cmd_maker(new, len))
	{
		// execution(get_infos());
		printf("%s\n", line);
		strnput(new, len);
		print_cmd(&get_infos()->cmd);
		// // printf("len : %zu\n", len);
		printf("\n");
	}
	free_cmd(&get_infos()->cmd);
	new = mms_free(new);
}
