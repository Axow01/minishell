
#ifndef PARSING_H
# define PARSING_H

# include "libftms/inc/libft.h"

# define QUOTES 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

void	parsing(char *str);
int		count_cmd_total(char *line, char delim);
void	init_cmd_struct(char *str);
bool	isinquote(char *str, size_t pos, size_t quote);
bool	isredirec(char *str);
void	strnput(char *str, size_t len);
void	free_cmd(t_command *lst);
void	print_cmd(t_command *lst);

#endif
