
#include "../../../includes/minishell.h"

void	print_double_char(char **dc)
{
	int			i;
	t_key_val	*vk;

	i = -1;
	while (dc[++i])
	{
		vk = export_get_key_val(dc[i]);
		printf("declare -x %s=\"%s\"\n", vk->key, vk->value);
		mms_free(vk->key);
		mms_free(vk->value);
		mms_free(vk);
	}
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
		dc[i] = mms_free(dc[i]);
	}
	dc = mms_free(dc);
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

static int	get_env_index(char *key, char **env, size_t n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], n) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (-1);
	return (i);
}

char	**ft_export(int ac, char **argv, char **env)
{
	char		**cpy_env;
	t_key_val	*vk;
	int			i;
	int			k;
	int			b;

	cpy_env = NULL;
	if (ac > 2)
		printf_error("minishell: ft_export: too much arguments\n");
	if (ac == 1)
	{
		print_double_char(env);
		return (env);
	}
	cpy_env = copy_double_char(env, ft_length_d_char(env));
	vk = export_get_key_val(argv[1]);
	i = get_env_index(vk->key, cpy_env, ft_strlen(vk->key));
	// Create new when i < 0.
	cpy_env[i] = mms_free(cpy_env[i]);
	cpy_env[i] = mms_alloc(ft_strlen(vk->key) + ft_strlen(vk->value) + 2, sizeof(char));
	k = 0;
	b = 0;
	while (vk->key[k])
		cpy_env[i][b++] = vk->key[k++];
	cpy_env[i][b++] = '=';
	k = 0;
	while (vk->value[k])
		cpy_env[i][b++] = vk->value[k++];
	return (cpy_env);
}
