/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:04:03 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 14:04:07 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
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

	if (!path)
		return (NULL);
	path_splited = ft_split(path, ':');
	mms_free(path);
	return (path_splited);
}

char	*get_cmd_path(char **cmd, char **path)
{
	int		i;
	char	*temp_path;

	i = -1;
	if (!path)
		return (NULL);
	while (path[++i])
	{
		temp_path = path[i];
		temp_path = ft_strjoin(temp_path, "/");
		temp_path = ft_strjoin(temp_path, cmd[0]);
		if (access(temp_path, F_OK | X_OK) == 0)
			return (temp_path);
		mms_free(temp_path);
	}
	return (NULL);
}
