
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
	int			i;
	int			k;
	t_key_val	*infos;

	i = 0;
	infos = mms_alloc(1, sizeof(t_key_val));
	while (raw_input[i])
	{
		if (raw_input[i] == '=')
		{
			k = -1;
			infos->key = mms_alloc(i + 1, sizeof(char));
			while (raw_input[++k] != '=')
				infos->key[k] = raw_input[k];
			break ;
		}
		i++;
	}
	if (!infos->key)
		no_equal(infos, raw_input);
	infos->value = mms_alloc(ft_strlen(&raw_input[i + 1]) + 1, sizeof(char));
	k = 0;
	while (raw_input[i] && raw_input[++i])
		infos->value[k++] = raw_input[i];
	return (infos);
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
	return (&env[i][n + 1]);
}
