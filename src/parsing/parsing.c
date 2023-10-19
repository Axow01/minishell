#include "minishell.h"
#include <stdio.h>
#include <string.h>

// t_temp	*get_redirec(void)
// {
// 	static t_temp	tmp;

// 	return (&tmp);
// }

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

// t_command	*ft_cmdnew(void)
// {
// 	t_command	*new;

// 	new = mms_alloc(1, sizeof(t_command));
// 	if (!new)
// 		return (NULL);
// 	new->next = NULL;
// 	return (new);
// }

// t_command	*ft_cmdlast(t_command *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_cmdadd(t_command **lst)
// {
// 	t_command	*new;
// 	t_command	*last;

// 	new = ft_cmdnew();
// 	last = ft_cmdlast(*lst);
// 	if (!new || !lst || !last)
// 		return ;
// 	if (!(*lst))
// 		*lst = new;
// 	else
// 		last->next = new;
// }

// void	init_cmd_struct(char *str)
// {
// 	int i;
// 	t_command *head;

// 	i = char_count(str, '|') + 1;
// 	head = &get_infos()->cmd;
// 	while (i > 0)
// 	{
// 		ft_cmdadd(&head);
// 		head = head->next;
// 		i--;
// 	}
// 	i = 0;
// 	head = &get_infos()->cmd;
// 	while (head->next != NULL)
// 		head = head->next;
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

#include <stdio.h>
#include <stdlib.h>

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

void custom_strtok(char **tokens, char *line, char delim) {
    int i = 0;
	char quote;

    while (*line != '\0') {
        if (*line == delim) {
            *line = '\0';
            line++;
        }
        tokens[i++] = line;
        quote = '\0';
        while (*line != '\0') {
            if (quote == '\0' && (*line == '\'' || *line == '"')) {
                quote = *line;
            } else if (quote != '\0' && *line == quote) {
                quote = '\0';
            } else if (quote == '\0' && *line == delim) {
                break;
            }
            line++;
        }
    }
    tokens[i] = NULL;
}

void teststrtok(char *line)
{

    int num_commands = count_tokens(line, '|');
    char **commands = mms_alloc(num_commands + 1, sizeof(char *));
    char ***parsed_commands = mms_alloc(num_commands + 1, sizeof(char **));
	int i;
	int j;
	int num_tokens;

	i = 0;
    custom_strtok(commands, line, '|');


    while (i < num_commands) {
        num_tokens = count_tokens(commands[i], ' ');
        parsed_commands[i] = mms_alloc(num_tokens + 1, sizeof(char *));
        custom_strtok(parsed_commands[i], commands[i], ' ');
		i++;
    }
    parsed_commands[num_commands] = NULL;
	i = 0;
    while (i < num_commands) {
        printf("Commande %d:\n", i);
		j = 0;
        while (parsed_commands[i][j]) {
            printf("  Token %d: %s\n", j, parsed_commands[i][j]);
			j++;
        }
		i++;
    }

	i = 0;
    while (i < num_commands) {
        free(parsed_commands[i]);
		i++;
    }
    free(parsed_commands);
    free(commands);
}