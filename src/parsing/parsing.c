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

char	*check_for_key(char *key, char **env, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		if (j == len && ft_strncmp(env[i], key, j) == 0)
			return (&env[i][j + 1]);
		i++;
	}
	return (NULL);
}


size_t dollars_key_len(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			break;
		i++;
	}
	return (i);
}

bool dollars_key_exist(char *key, size_t len)
{
	if (check_for_key(key, get_infos()->env, len) && len > 0)
		return (true);
	return (false);
}

size_t dollars_count(char *str)
{
	size_t i;
	size_t count;
	size_t dollars_len;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !isinquote(str, i, SINGLE_QUOTE))
		{
			dollars_len = dollars_key_len(&str[i + 1]);
			// printf("dol : %d\n", dollars_key_exist(&str[i + 1], dollars_len));
			// printf("dolen : %zu\n", dollars_len);
			count += ft_strlen(check_for_key(&str[i + 1], get_infos()->env, dollars_len)) - (dollars_len);
		}
		i++;
	}
	return (count);
}

void dollars_token_copy(char *str, char *new_line, size_t *i, size_t *j)
{
	char *token;
	size_t dollars_len;

	dollars_len = dollars_key_len(&str[*i + 1]);
	if (dollars_key_exist(&str[*i + 1], dollars_len) && str[*i + 1])
	{
		token = check_for_key(&str[*i + 1], get_infos()->env, dollars_len);
		while (*token)
		{
			new_line[*j] = *token;
			token++;
			*j += 1;
		}
		*i += dollars_len + 1;
	}
	else if (!dollars_key_exist(&str[*i + 1], dollars_len) || !str[*i + 1])
	{
		if (dollars_len > 0)
			*i += dollars_len + 1;
		else
		{
			*i += 1;
		}
		return ;
	}
}

char *setup_line(char *str, size_t *len)
{
	size_t i;
	size_t j;
	char *new_line;

	*len = count_redirection(str) + ft_strlen(str) + dollars_count(str);
	// printf("dollars_count: %zu\n", dollars_count(str));
	// printf("redir : %zu\n", count_redirection(line));
	// printf("stlen : %zu\n", ft_strlen(line));
	if (*len == 0)
		return (NULL);
	new_line = mms_alloc(*len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '$' && str[i + 1] == '$' && !isinquote(str, i, SINGLE_QUOTE))
		{
			new_line[j++] = '$';
			i += 2;
		}
		while (str[i] == '$' && str[i + 1] != '$' && !isinquote(str, i, SINGLE_QUOTE))
			dollars_token_copy(str, new_line, &i, &j);
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
	printf("%s\n", new);
	init_cmd_struct(line);
	replace_space(new, 0, len);
	cmd_maker(new, len);
	// execution(get_infos());
	strnput(new, len);
	// printf("len : %zu\n", len);
	print_cmd(&get_infos()->cmd);
	printf("\n");
	free_cmd(&get_infos()->cmd);
}
//echo "yolo bg">txt.out | wc -l
