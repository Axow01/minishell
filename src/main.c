#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int i = 0;

	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}
