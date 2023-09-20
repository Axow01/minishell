
#include "../../../includes/minishell.h"

void	cd(char *new_path, char **env)
{
	int	i;

	(void)new_path;
	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}
