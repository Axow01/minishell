#include "minishell.h"
#include <stdio.h>
#include <string.h>

// size_t	char_count(char *str, char c)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }


// size_t count_str(char *str, char *delim)
// {
// 	size_t i;
// 	size_t len;
// 	size_t count;

// 	i = 0;
// 	count = 0;
// 	len = ft_strlen(delim);
// 	while (str[i])
// 	{
// 		if (ft_strncmp(&str[i], delim, len) == 0)
// 		{
// 			count++;
// 			if (i + len > ft_strlen(str))
// 				return (count);
// 			i += len;
// 		}
// 		else
// 			i++;
// 	}
// 	return (count);
// }

// int	count_len(char *str)
// {
// 	size_t i;
// 	size_t count;
// 	bool in_single_quote;
// 	bool in_double_quote;

// 	i = 0;
// 	count = 1;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' && !in_single_quote)
//             in_double_quote = !in_double_quote;
//         else if (str[i] == '\'' && !in_double_quote)
//             in_single_quote = !in_single_quote;
// 		if (!in_single_quote && !in_double_quote)
// 		{
// 			if (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i], "<<", 2) == 0)
// 			{
// 				count++;
// 				i += 2;
// 			}
// 			else if (str[i] == '>' || str[i] == '<')
// 				count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

bool isredirec(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0 
		|| ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
		return (true);
	return (false);
}

bool isinquote(char *str, size_t len, size_t quote)
{
	bool in_single_quote;
	bool in_double_quote;
	size_t i;

	i = 0;
    in_single_quote = false;
	in_double_quote = false;
	if (len == 0 || !str)
		return (false);
	while (i <= len)
	{
		if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		i++;
	}
	if (quote == QUOTE && (in_single_quote || in_double_quote))
		return (true);
	else if (quote == SINGLE_QUOTE && in_single_quote)
		return (true);
	else if (quote == DOUBLE_QUOTE && in_double_quote)
		return (true);
	return (false);
}

t_command	*ft_cmdnew(void)
{
	t_command	*new;

	new = mms_alloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

t_command	*ft_cmdlast(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_cmdadd(t_command **lst)
{
	t_command	*new;
	t_command	*last;

	new = ft_cmdnew();
	last = ft_cmdlast(*lst);
	if (!new || !lst || !last)
		return ;
	if (!(*lst))
		*lst = new;
	else
		last->next = new;
}


void	init_cmd_struct(char *str)
{
	int i;
	t_command *head;

	i = count_cmd_total(str, '|');
	head = &get_infos()->cmd;
	while (i - 1 > 0)
	{
		ft_cmdadd(&head);
		head = head->next;
		i--;
	}
}

int count_cmd_total(char *str, char delim)
{
    int count;
	int i;

	i = 0;
	count = 1;
    while (str[i]) {
		if (!isinquote(str, i, QUOTE))
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
		if (!isinquote(str, i, QUOTE))
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
		if (!isinquote(str, i, QUOTE))
		{
			if (str[i] == '|')
			{
				count++;
			}
			while (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i], "<<", 2) == 0)
			{
				count += 1;
				i += 2;
			}
			if (str[i] == '>' || str[i] == '<')
				count += 1;
		}
		i++;
	}
	return (count);
}

char *setup_line(char *str, size_t *len)
{
	size_t i;
	size_t j;
	char *new_line;

	*len = count_redirection(str) * 2 + ft_strlen(str);
	// printf("redir : %zu\n", count_redirection(line));
	// printf("stlen : %zu\n", ft_strlen(line));
	if (*len == 0)
		return (NULL);
	new_line = mms_alloc(*len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!isinquote(str, i, QUOTE))
		{
			if (str[i] == '|' && !isinquote(str, i, QUOTE))
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

void ft_strput(char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i <= len)
	{
		if (str[i] == '\0')
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

void get_element(char *line, size_t start, size_t end, t_command *head)
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

			head->cmd[j++] = &line[ptr];
			while (line[i] == '\0' && i < end)
				i++;
			ptr = i;
		}
		i++;
    }
}

size_t count_element(char *line, size_t start, size_t end)
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

void controller(char *str, size_t len)
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
		if ((str[i] == '|' && !isinquote(str, i, QUOTE)) || i == len)
		{
			end = i;
			// printf("Start: %zu End: %zu\n", start, end);
			head->cmd = mms_alloc(count_element(str, start, end) + 1, sizeof(char *));
			head->stdin_ = STDIN_FILENO;
			head->stdout_ = STDOUT_FILENO;
			get_element(str, start, end, head);
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

void	print_cmd(t_command *lst)
{
	size_t i;
	size_t j;
	t_command *head;

	i = 0;
	head = lst;
	while (head)
	{
		// printf("in: %d out: %d\n", head->stdin_, head->stdout_);
		printf("command%lu : \n", i);
		j = 0;
		while (head->cmd && head->cmd[j])
		{
			printf("token%lu : %s\n", j, head->cmd[j]);
			j++;
		}
		i++;
		head = head->next;
	}
}

void	free_cmd(t_command *lst)
{
	t_command *head;
	t_command *temp;
	size_t j;

	head = lst;
	j = 0;
	while (head)
	{
		j = 0;
		while (head->cmd && head->cmd[j])
		{
			mms_free(head->cmd[j]);
			j++;
		}
		head = head->next;
	}
	head = lst;
	head = head->next;
	while (head)
	{
		temp = head;
		head = head->next;
		mms_free(temp);
  	}
	head = lst;
	head->next = NULL;
}

void teststrtok(char *line)
{
	char *new;
	size_t len;
	new = setup_line(line, &len);
	if (new == NULL)
		return ;
	init_cmd_struct(line);
	replace_space(new, 0, len);
	controller(new, len);
	execution(get_infos());
	// ft_strput(new, len);
	// printf("len : %zu\n", len);
	// print_cmd(&get_infos()->cmd);
	// free_cmd(&get_infos()->cmd);
}
//echo "yolo bg">txt.out | wc -l