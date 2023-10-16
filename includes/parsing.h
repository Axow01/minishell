#ifndef PARSING_H
# define PARSING_H

# include "libftms/inc/libft.h"

typedef struct s_temp
{
	char	**redirec;
	int		index;

}			t_temp;

void		teststrtok(char *str);
char		*ft_strtok(char *str, const char delim);
char		*ft_strtok_2(char *str, const char delim);
t_temp		*get_redirec(void);

#endif
