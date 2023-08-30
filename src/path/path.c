
#include "../../includes/minishell.h"

char	*env_to_path(char **env)
{
	int		i;
	int		k;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			k = 4;
			path = mms_alloc(ft_strlen(env[i] + k) + 1, sizeof (char));
			while (env[i][++k])
				path[k - 5] = env[i][k];
			break ;
		}
		i++;
	}
	return (path);
}

char	**path_split(char *path)
{
	char	**path_splited;

	path_splited = ft_split(path, ':');
	path = mms_free(path);
	return (path_splited);
}
