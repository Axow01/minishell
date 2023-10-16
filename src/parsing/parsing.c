
#include "../../includes/parsing.h"
#include <stdio.h>
#include <string.h>

t_temp	*get_redirec(void)
{
	static t_temp	tmp;

	return (&tmp);
}

void	teststrtok(char *str)
{
	char *token;
	get_redirec()->redirec = mms_alloc(ft_strlen(str), sizeof(char *));
	token = ft_strtok(str, '|');
	while (token != NULL)
	{
	    printf("val : %s\n", get_redirec()->redirec[get_redirec()->index]);
		printf("token : %s\n", token);
		get_redirec()->index += 1;
		token = ft_strtok(NULL, '|');
		
	}

}