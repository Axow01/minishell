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

void replace_space(char *line, size_t start, size_t end)
{
	size_t 	i;
	bool 	in_single_quote;
	bool 	in_double_quote;

	i = start;
	in_single_quote = false;
	in_double_quote = false;
	(void)line;
	while (i < end)
	{
		if (line[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (line[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (ft_isspace(line[i]))
				line[i] = '\0';
		}
		i++;
	}
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

int count_tokens(char *line, char delim) {
    int count;
	int i;

	i = 0;
	count = 1;
    while (line[i]) {
        if (line[i] == delim) {
            count++;
        }
		i++;
    }
    return count;
}

void	init_cmd_struct(char *str)
{
	int i;
	t_command *head;

	i = count_tokens(str, '|');
	head = &get_infos()->cmd;
	while (i > 0)
	{
		ft_cmdadd(&head);
		head = head->next;
		i--;
	}
	i = 0;
	head = &get_infos()->cmd;
	while (head->next != NULL)
		head = head->next;
}

size_t count_element(char *line, size_t start, size_t end)
{
	size_t i;
	size_t count;
	bool 	in_single_quote;
	bool 	in_double_quote;

	i = start;
	count = 1;
	while (i < end)
	{
		if (line[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (line[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (line[i] == '\0')
			{
				while(line[i] == '\0' && i < end)
					i++;
				if (i != end)
					count++;
			}
		}
		i++;
	}
	return (count);
}

int	count_redirection(char *str)
{
	size_t i;
	size_t count;
	bool in_single_quote;
	bool in_double_quote;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (str[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (ft_strncmp(&str[i], ">>", 2) == 0 || ft_strncmp(&str[i], "<<", 2) == 0)
			{
				count += 2;
				i += 2;
			}
			else if (str[i] == '>' || str[i] == '<')
				count += 2;
		}
		i++;
	}
	return (count);
}

char *resize_line(char *line)
{
	size_t i;
	size_t j;
	size_t new_size;
	char *new_line;
	bool in_single_quote;
	bool in_double_quote;

	new_size = count_redirection(line) + ft_strlen(line) + 1;
	new_line = mms_alloc(new_size + 1, sizeof(char));

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        else if (line[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
		if (!in_single_quote && !in_double_quote)
		{
			if (ft_strncmp(&line[i], ">>", 2) == 0 || ft_strncmp(&line[i], "<<", 2) == 0)
			{
				new_line[j++] = '\0';
				new_line[j++] = line[i++];
				new_line[j++] = line[i++];
				new_line[j++] = '\0';
			}
			else if (line[i] == '>' || line[i] == '<')
			{
				new_line[j++] = '\0';
				new_line[j++] = line[i++];
				new_line[j++] = '\0';
			}
			if (ft_isspace(line[i]))
			{
				new_line[j++] = '\0';
				i++;
			}
		}
		new_line[j++] = line[i++];
	}
	return (new_line);
}

void ft_strput(char *str, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '\0')
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}


void controller(char *line)
{
	size_t i;
	size_t end;
	size_t start;

	i = 0;
	while(line[i])
	{
		start = i;
		if (line[i] == '|' || line[i+1] == '\0')
		{
			end = i;
			count_element(line, start, end);
			ft_strput(line, end);
		}
		i++;
	}
}

void teststrtok(char *line)
{
   char *new;

   new = resize_line(line);
   replace_space(new, 0, 20);
   ft_strput(new, 20);

}