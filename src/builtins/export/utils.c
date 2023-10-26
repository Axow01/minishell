
#include "../../../includes/minishell.h"

t_key_val	*export_get_key_val(char *raw_input)
{
	int			i;
	int			k;
	t_key_val	*infos;

	i = 0;
	k = 0;
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
	infos->value = mms_alloc(ft_strlen(&raw_input[i + 1]) + 1, sizeof(char));
	k = 0;
	while (raw_input[++i])
		infos->value[k++] = raw_input[i];
	return (infos);
}
