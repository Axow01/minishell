/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:57:22 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:57:24 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_cmd(t_command *lst)
// {
// 	size_t		i;
// 	size_t		j;
// 	t_command	*head;

// 	i = 0;
// 	head = lst;
// 	while (head)
// 	{
// 		printf("in: %d out: %d\n", head->stdin_, head->stdout_);
// 		printf("tmp: command%lu : \n", i);
// 		j = 0;
// 		while (head->tmp && head->tmp[j])
// 		{
// 			printf("tmp: token%lu : %s\n", j, head->tmp[j]);
// 			j++;
// 		}
// 		printf("cmd: command%lu : \n", i);
// 		j = 0;
// 		while (head->cmd && head->cmd[j])
// 		{
// 			printf("cmd: token%lu : %s\n", j, head->cmd[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 		head = head->next;
// 	}
// }

void	strnput(char *str, size_t len)
{
	size_t	i;

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

int	digit_counter(long long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	**ft_sfree_2d(void **ptr)
{
	void	**temp;

	if (!ptr)
		return (NULL);
	temp = ptr;
	while (*ptr)
		mms_free(*ptr++);
	mms_free(temp);
	return (NULL);
}

char	**copy_double_char(char **dc)
{
	size_t	i;
	char	**tmp;

	i = 0;
	tmp = mms_alloc(len_double_char(dc) + 1, sizeof(char *));
	while (dc && dc[i])
	{
		tmp[i] = ft_strdup(dc[i]);
		i++;
	}
	return (tmp);
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
			head->cmd[j++] = ft_strdup(head->tmp[i]);
		if (head->tmp[i])
			i++;
	}
}
