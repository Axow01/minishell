
#include "../includes/minishell.h"

t_infos	*get_infos(void)
{
	static t_infos	*infos;

	if (!infos)
	{
		infos = mms_alloc(1, sizeof(t_infos));
		infos->cmd = NULL;
		infos->env = NULL;
	}
	return (infos);
}

int	main(int argc, char **argv, char **env)
{
	t_infos	*infos;

	(void)argc;
	mms_set_alloc_fn(ft_calloc);
	infos = get_infos();
	infos->cmd = argv;
	infos->env = env;
	infos->path = path_split(env_to_path(infos->env));
	infos->cmd = mms_alloc(2, sizeof(char **));
	infos->cmd[1] = 0;
	infos->cmd[0] = readline("minishell>");
	if (!infos->cmd[0])
		mms_kill("Input error!\n", true, 1);
	printf("Execution success: %d\n", execution(get_infos()));
	mms_kill("", false, 0);
	return (0);
}
