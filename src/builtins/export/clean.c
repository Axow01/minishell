
#include "../../../includes/minishell.h"

void	clean_vk(t_key_val *vk, char **cpy_env)
{
	if (!vk)
		return ;
	vk->key = mms_free(vk->key);
	vk->value = mms_free(vk->value);
	vk = mms_free(vk);
	get_infos()->env = cpy_env;
	get_infos()->latest_error_code = 0;
}

void	initiate_keys(char *raw_input, t_key_val *infos)
{
	int	i;
	int	k;

	i = 0;
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
}
