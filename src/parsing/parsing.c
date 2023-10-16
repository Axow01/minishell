
#include "minishell.h"
#include <stdio.h>
#include <string.h>

t_temp	*get_redirec(void)
{
	static t_temp	tmp;

	return (&tmp);
}

size_t	char_count(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	count_len(char *str)
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
				count++;
				i += 2;
			}
			else if (str[i] == '>' || str[i] == '<')
				count++;
		}
		i++;
	}
	return (count);
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

	i = char_count(str, '|') + 1;
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

void	teststrtok(char *str)
{
	int i;

	i = 1;
	init_cmd_struct(str);
	printf("tes:%d\n", count_len(str));
	get_infos()->cmd.cmd = mms_alloc(count_len(str)+1, sizeof(char *));
	get_infos()->cmd.cmd[0] = ft_strtok(str, '|');
	while (get_infos()->cmd.cmd[i] != NULL)
	{
		printf("token : %s\n", get_infos()->cmd.cmd[i]);
		get_infos()->cmd.cmd = mms_alloc(count_len(str)+1, sizeof(char *));
		get_infos()->cmd.cmd[i] = ft_strtok(NULL, '|');
		i++;
	}
}