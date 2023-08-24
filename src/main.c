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
	int		i;
	int		b;

	(void)argc;
	(void)argv;

	mms_set_alloc_fn(ft_calloc);
	infos = get_infos();
	infos->env = env;
	infos->cmd = (char **)mms_alloc(4, sizeof(char *));
	infos->cmd[0] = mms_alloc(10, sizeof(char));
	infos->cmd[1] = mms_alloc(10, sizeof(char));
	infos->cmd[2] = mms_alloc(10, sizeof(char));
	infos->cmd[3] = mms_alloc(1, sizeof(char));
	infos->cmd[3][0] = 0;
	i = 0;
	while (i < 4)
	{
		b = -1;
		while (++b < 9 && i != 3)
			infos->cmd[i][b] = 'z';
		i++;
	}
	printf("%d\n", execution(get_infos()));
	mms_kill("", false, 0);
	return (0);
}
