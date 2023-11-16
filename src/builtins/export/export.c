
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

char	**copy_double_char(char **dc, int n)
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

size_t	ft_length_d_char(char **dc)
{
	int	i;

	i = 0;
	if (!dc)
		return (0);
	while (dc[i])
		i++;
	return (i);
}

int	get_env_index(char *key, char **env, size_t n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], n) == 0 && env[i][n] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (-1);
	return (i);
}

void	export_pars_err(int err)
{
	if (err != -1)
		printf("export: not an identifier\n");
}

bool	export_pars(char *str, int *err)
{
	size_t	i;

	i = 0;
	if (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
		i++;
	while (str[i] && (str[i] == '_' || ft_isalpha(str[i]) || ft_isalnum(str[i])))
		i++;
	if ((str[i] != '=' || i < ft_strlen(str)) && *err == -1)
	{
		*err = i;
		return(false);
	}
	return (true);
}

void	ft_export(int ac, char **argv, char **env)
{
	char		**cpy_env;
	t_key_val	*vk;
	int			i;
	int			ac_i;
	int			err;

	err = -1;
	ac_i = 0;
	cpy_env = env;
	vk = NULL;
	if (ac == 1)
		print_double_char(env);
	while (argv[++ac_i] && ac > 1)
	{
		if (export_pars(argv[ac_i], &err))
		{
			cpy_env = copy_double_char(cpy_env, ft_length_d_char(cpy_env));
			vk = export_get_key_val(argv[ac_i]);
			i = get_env_index(vk->key, cpy_env, ft_strlen(vk->key));
			if (i < 0)
				cpy_env = create_new_variable(vk, cpy_env);
			else
				edit_variable(vk, cpy_env, i);
		}
	}
	export_pars_err(err);
	clean_vk(vk, cpy_env);
}
