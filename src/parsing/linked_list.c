#include "minishell.h"

static t_command	*ft_cmdnew(void)
{
	t_command	*new;

	new = mms_alloc(1, sizeof(t_command));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

static t_command	*ft_cmdlast(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static void	ft_cmdadd(t_command **lst)
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

size_t dollars_pipe(char *str)
{
	size_t i;
	size_t count;
	char *token;

	token = NULL;
	count = 0;
	i  = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && !isinquote(str, i, QUOTES))
		{
			if (dollars_key_exist(&str[i + 1], dollars_key_len(&str[i + 1])))
			{
				token = check_for_key(&str[i + 1],
					get_infos()->env, dollars_key_len(&str[i + 1]));
				count += char_count(token, '|');
				token = mms_free(token);
			}
		}
		i++;
	}
	return (count);
}

void	init_cmd_struct(char *str)
{
	int			i;
	t_command	*head;

	i = count_cmd_total(str, '|') + dollars_pipe(str);
	head = &get_infos()->cmd;
	while (i - 1 > 0)
	{
		ft_cmdadd(&head);
		head = head->next;
		i--;
	}
}
