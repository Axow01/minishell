#include "minishell.h"
#include <stdio.h>
#include <string.h>

int count_cmd_total(char *str, char delim)
{
    int count;
	int i;

	i = 0;
	count = 1;
    while (str[i]) {
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == delim) {
				count++;
			}
		}
		i++;
    }
    return count;
}

void replace_space(char *str, size_t start, size_t end)
{
	size_t 	i;

	i = start;
	while (i < end)
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (ft_isspace(str[i]))
				str[i] = '\0';
		}
		i++;
	}
}

size_t	count_redirection(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == '|')
			{
				count += 2;
			}
			while (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i], "<<", 2) == 0)
			{
				count += 2;
				i += 2;
			}
			if (str[i] == '>' || str[i] == '<')
				count += 2;
		}
		i++;
	}
	return (count);
}

size_t ft_dollars_len(char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			break;
		i++;
	}
	return (i);
}

char *setup_line(char *str, size_t *len)
{
	size_t i;
	size_t j;
	char *new_line;

	*len = count_redirection(str) + ft_strlen(str);
	// printf("redir : %zu\n", count_redirection(line));
	// printf("stlen : %zu\n", ft_strlen(line));
	if (*len == 0)
		return (NULL);
	new_line = mms_alloc(*len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!isinquote(str, i, QUOTES))
		{
			if (str[i] == '|' && !isinquote(str, i, QUOTES))
			{
				new_line[j++] = ' ';
				new_line[j++] = str[i++];
				new_line[j++] = ' ';
			}
			while (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i], "<<", 2) == 0)
			{
				new_line[j++] = ' ';
				new_line[j++] = str[i++];
				new_line[j++] = str[i++];
				new_line[j++] = ' ';
			}
			if (str[i] == '>' || str[i] == '<')
			{
				new_line[j++] = ' ';
				new_line[j++] = str[i++];
				new_line[j++] = ' ';
			}
		}
		new_line[j++] = str[i++];
	}
	return (new_line);
}

void get_token(char *line, size_t start, size_t end, t_command *head)
{
    size_t i;
    size_t j;
	size_t ptr;

    i = start;
	j = 0;
	while (line[i] == '\0' && i < end)
		i++;
	ptr = i;
    while (i <= end)
    {
        if (line[i] == '\0')
		{

			head->cmd[j++] = ft_strdup(&line[ptr]);
			while (line[i] == '\0' && i < end)
				i++;
			ptr = i;
		}
		i++;
    }
}

size_t count_token(char *line, size_t start, size_t end)
{
	size_t i;
	size_t count;

	i = start;
	count = 1;
	while(line[i] == '\0' && i < end)
		i++;
	while (i < end)
	{
			if (line[i] == '\0')
			{
				while(line[i] == '\0' && i < end)
					i++;
				if (i < end)
					count++;
			}
		i++;
	}
	return (count);
}

void cmd_maker(char *str, size_t len)
{
	size_t i;
	size_t end;
	size_t start;
	t_command *head;

	i = 0;
	start = 0;
	head = &get_infos()->cmd;
	while(i <= len)
	{
		if ((str[i] == '|' && !isinquote(str, i, QUOTES)) || i == len)
		{
			end = i;
			// printf("Start: %zu End: %zu\n", start, end);
			head->cmd = mms_alloc(count_token(str, start, end) + 1, sizeof(char *));
			head->stdin_ = STDIN_FILENO;
			head->stdout_ = STDOUT_FILENO;
			get_token(str, start, end, head);
			if (head->cmd && head->cmd[0] && !head->cmd[0][0])
			{
				printf("minishell : syntax error near unexpected token `|'\n");
				return ;
			}
			head = head->next;
			start = end + 1;
		}
		i++;
	}
}

void parsing(char *line)
{
	char *new;
	size_t len;
	new = setup_line(line, &len);
	if (new == NULL)
		return ;
	init_cmd_struct(line);
	replace_space(new, 0, len);
	cmd_maker(new, len);
	// execution(get_infos());
	strnput(new, len);
	// printf("len : %zu\n", len);
	print_cmd(&get_infos()->cmd);
	free_cmd(&get_infos()->cmd);
}
//echo "yolo bg">txt.out | wc -l
