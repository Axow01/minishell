#include "../../../includes/minishell.h"

static void	no_equal(t_key_val *vk, char *raw_input)
{
	int	i;

	vk->key = mms_alloc(ft_strlen(raw_input) + 1, sizeof(char));
	i = -1;
	while (raw_input[++i])
		vk->key[i] = raw_input[i];
}

t_key_val	*export_get_key_val(char *raw_input)
{
	int			k;
	int			i;
	t_key_val	*infos;

	if (!raw_input)
		return (NULL);
	infos = mms_alloc(1, sizeof(t_key_val));
	i = initiate_keys(raw_input, infos);
	if (!infos->key)
		no_equal(infos, raw_input);
	infos->value = mms_alloc(ft_strlen(&raw_input[i]) + 1, sizeof(char));
	k = 0;
	while (raw_input[i] && raw_input[++i])
		infos->value[k++] = raw_input[i];
	return (infos);
}

char	*check_for_key_export(char *key, char **env, size_t n)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(key, env[i], n) == 0 && env[i][n] == '=')
			break ;
		i++;
	}
	return (&env[i][n + 1]);
}

char	**create_new_variable(t_key_val *vk, char **env)
{
	int	i;
	int	k;
	int	d;

	if (!env)
		return (env);
	i = len_double_char(env);
	k = 0;
	d = 0;
	env = copy_double_charf(env, i + 1);
	env[i] = mms_alloc(ft_strlen(vk->key)
			+ ft_strlen(vk->value) + 2, sizeof(char));
	while (vk->key[k])
		env[i][d++] = vk->key[k++];
	k = 0;
	env[i][d++] = '=';
	while (vk->value[k])
		env[i][d++] = vk->value[k++];
	return (env);
}

void	edit_variable(t_key_val *vk, char **env, int i)
{
	int	k;
	int	b;

	env[i] = mms_free(env[i]);
	env[i] = mms_alloc(ft_strlen(vk->key)
			+ ft_strlen(vk->value) + 2, sizeof(char));
	k = 0;
	b = 0;
	while (vk->key[k])
		env[i][b++] = vk->key[k++];
	env[i][b++] = '=';
	k = 0;
	while (vk->value[k])
		env[i][b++] = vk->value[k++];
}
