
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
