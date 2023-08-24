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
	execution(infos);
	mms_kill("", false, 0);
	return (0);
}
