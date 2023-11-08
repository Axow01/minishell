
#include "../../../includes/minishell.h"

void	ft_env(int argc, char **argv, char **env)
{
	int	i;

	i = -1;
	get_infos()->latest_error_code = 1;
	if (!env)
		return ;
	if (argc != 1)
	{
		printf_error("minishell: ft_env: too much arguments\n");
		return ;
	}
	(void)argv;
	while (env[++i])
		printf("%s\n", env[i]);
	get_infos()->latest_error_code = 0;
}
