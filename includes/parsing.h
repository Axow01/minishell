
#ifndef PARSING_H
# define PARSING_H

# include "libftms/inc/libft.h"

typedef struct s_temp
{
	char	**redirec;
	int		index;

}			t_temp;

void		teststrtok(char *str);
char		*ft_strtok(char *str);
char		*ft_strtok_redirect(char *str);

#endif
