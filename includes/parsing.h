
#ifndef PARSING_H
# define PARSING_H

# include "libftms/inc/libft.h"

# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

void	teststrtok(char *str);
char	*ft_strtok(char *str);
char	*ft_strtok_redirect(char *str);
int		count_tokens(char *line, char delim);
bool	ft_isinquote(char *str, size_t len);

#endif
