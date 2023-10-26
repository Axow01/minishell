#include "minishell.h"

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

void strnput(char *str, size_t len)
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