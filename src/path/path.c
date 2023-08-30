
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

char	*get_cmd_path(char **cmd, char **path)
{
	int		i;
	char	*temp_path;

	i = -1;
	while (path[++i])
	{
		temp_path = path[i];
		temp_path = ft_strjoin(temp_path, "/");
		temp_path = ft_strjoin(temp_path, cmd[0]);
		if (access(temp_path, F_OK | X_OK) == 0)
			return (temp_path);
		temp_path = mms_free(temp_path);
	}
	return (NULL);
}

char	*get_pwd(char **env)
{
	char	*pwd;
	char	*tmp;
	int		k;
	int		i;

	pwd = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
		{
			k = 3;
			pwd = mms_alloc(ft_strlen(env[i] + 4) + 2, sizeof (char));
			while (env[i][++k])
				pwd[k - 4] = env[i][k];
			pwd[k - 4] = '>';
			tmp = ft_strjoin(pwd, "\x1b[0m");
			pwd = mms_free(pwd);
			return (tmp);
		}
	}
	return (NULL);
}
