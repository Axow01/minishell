#include "../../../includes/minishell.h"

static bool	is_indexed(int i, int *index, int size)
{
	int	in;

	in = 0;
	while (in < size)
		if (index[in++] == i)
			return (true);
	return (false);
}

static void	create_new_env(char **env, int new_size, int *index, int size)
{
	int		i;
	int		k;
	int		l;
	char	**new_env;

	i = -1;
	k = -1;
	new_env = mms_alloc(new_size + 1, sizeof(char *));
	while (env[++i])
	{
		l = -1;
		if (is_indexed(i, index, size))
		{
			env[i] = mms_free(env[i]);
			continue ;
		}
		new_env[++k] = mms_alloc(ft_strlen(env[i]) + 1, sizeof(char));
		while (env[i][++l])
			new_env[k][l] = env[i][l];
		env[i] = mms_free(env[i]);
	}
	env = mms_free(env);
	get_infos()->env = new_env;
}

static void	unset_value(char **env, int *index, int n)
{
	int	i;
	int	b;

	i = -1;
	b = 0;
	while (++i < n)
		if (index[i] >= 0)
			b++;
	create_new_env(env, len_double_char(env) - b, index, n);
}

void	ft_unset(int argc, char **argv, char **env)
{
	int		i;
	char	**cpy_env;
	int		*index;

	i = -1;
	cpy_env = env;
	if (!cpy_env)
	{
		printf_error(1, "minishell: ft_unset: env error\n");
		return ;
	}
	if (argc < 2)
	{
		printf_error(1, "minishell: ft_unset: not enough arguments\n");
		return ;
	}
	index = mms_alloc(argc, sizeof(int));
	while (argv[++i])
		index[i] = get_env_index(argv[i], cpy_env, ft_strlen(argv[i]));
	unset_value(cpy_env, index, argc);
}
