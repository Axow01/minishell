
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

char	**copy_double_charf(char **dc, int n)
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

size_t	len_double_char(char **dc)
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

void	export_pars_err(char **av, int err)
{
	int		i;
	char	*token;

	i = 0;
	token = NULL;
	if (err != -1)
	{
		while (av[err][i])
		{
			if (av[err][i] == '=' && av[err][i + 1] != '=')
				break ;
			i++;
		}
		token = mms_alloc(i + 1, sizeof(char));
		ft_strlcpy(token, av[err], i + 1);
		printf("export: not an identifier: %s\n", token);
		get_infos()->latest_error_code = 1;
		token = mms_free(token);
	}
}

bool	export_pars(char *str, int *err, int ac_i)
{
	size_t	i;

	i = 0;
	if (str[i] == '=' || ft_isdigit(str[i]))
	{
		if (*err == -1)
			*err = ac_i;
		return (false);
	}
	if (str[i] && (str[i] == '_' || ft_isalpha(str[i])))
		i++;
	while (str[i])
	{
		if (str[i] == '=' || (!ft_isalpha(str[i]) && !ft_isdigit(str[i])))
			break ;
		i++;
	}
	if (str[i] == '=' && str[i + 1] == '=')
		return (*err = ac_i, false);
	else if (!str[i] || str[i] == '=')
		return (true);
	else if (*err == -1)
		*err = ac_i;
	return (false);
}

void	print_double_char_al(char **env)
{
	size_t i;
	char *tmp;
	char **dc;

	i = 0;
	dc = copy_double_char(env);
	while (dc && dc[i])
	{
		if (ft_strncmp(dc[i], dc[i + 1], ft_strlen(dc[i]) + 1) > 0)
		{
			tmp = dc[i + 1];
			dc[i + 1] = dc[i];
			dc[i] = tmp;
			i = -1;
		}
		i++;
	}
	print_double_char(dc);
	dc = (char **)ft_sfree_2d((void **)dc);
}

void init_export(int *err, int *ac_i)
{
	*err = -1;
	*ac_i = 0;
}

void	ft_export(int ac, char **argv, char **env)
{
	char		**cpy_env;
	t_key_val	*vk;
	int			i;
	int			ac_i;
	int			err;

	cpy_env = env;
	init_export(&err, &ac_i);
	vk = NULL;
	if (ac == 1)
		return (print_double_char_al(cpy_env));
	while (argv[++ac_i] && ac > 1)
	{
		if (!export_pars(argv[ac_i], &err, ac_i))
			continue ;
		cpy_env = copy_double_charf(cpy_env, len_double_char(cpy_env));
		vk = export_get_key_val(argv[ac_i]);
		i = get_env_index(vk->key, cpy_env, ft_strlen(vk->key));
		if (i < 0)
			cpy_env = create_new_variable(vk, cpy_env);
		else
			edit_variable(vk, cpy_env, i);
	}
	clean_vk(vk, cpy_env);
	export_pars_err(argv, err);
}
