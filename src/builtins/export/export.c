
#include "../../../includes/minishell.h"

void	print_double_char(char **dc)
{
	int	i;

	i = -1;
	while (dc[++i])
		ft_printf("%s\n", dc[i]);
}

static char	**copy_double_char(char **dc, int n)
{
	char	**cpy;
	int		i;
	int		k;

	cpy = mms_alloc(n + 1, sizeof(char *));
	i = -1;
	while (dc[++i])
	{
		k = -1;
		cpy[i] = mms_alloc(ft_strlen(dc[i]) + 1, sizeof(char));
		while (dc[i][++k])
			cpy[i][k] = dc[i][k];
	}
	return (cpy);
}

static size_t	ft_length_d_char(char **dc)
{
	int	i;

	i = 0;
	if (!dc)
		return (0);
	while (dc[i])
		i++;
	return (i);
}

char	*check_for_key(char *key, char **env, size_t n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], n) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

char	**ft_export(int ac, char **argv, char **env)
{
	char		**cpy_env;
	t_key_val	*vk;

	cpy_env = NULL;
	if (ac > 2)
		printf_error("minishell: ft_export: too much arguments\n");
	if (ac == 1)
		print_double_char(env);
	cpy_env = copy_double_char(env, ft_length_d_char(env));
	vk = export_get_key_val(argv[1]);
	if (check_for_key(vk->key, cpy_env, ft_strlen(vk->key)) == NULL)
	{
		ft_printf("The value is non-existant.\n");
	}
	else
		ft_printf("The value exist. KEY: %s Value: %s\n", vk->key, vk->value);
	return (cpy_env);
}
