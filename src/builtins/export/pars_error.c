/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:58:51 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 13:58:53 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	size_t	i;
	char	*tmp;
	char	**dc;

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
