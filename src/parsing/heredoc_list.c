// #include "minishell.h"

// t_heredoc *new_heredoc_line(char *str)
// {
//     t_heredoc *new;

//     new = mms_alloc(1, sizeof(t_heredoc));
//     if (!new)
// 		return (NULL);
//     new->str = str;
// 	new->next = NULL;
// 	return (new);
// }

// static t_heredoc	*last_heredoc_line(t_heredoc *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void add_heredoc_line(t_heredoc **heredoc, char *str)
// {
//     t_heredoc   *new;
// 	t_heredoc   *last;

// 	new = last_heredoc_line(str);
// 	last = ft_cmdlast(*heredoc);
// 	if (!new || !heredoc || !last)
// 		return ;
// 	if (!(*heredoc))
// 		*heredoc = new;
// 	else
// 		last->next = new;
// }
