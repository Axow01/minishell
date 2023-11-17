/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:57:59 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 13:58:34 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	init_export(int *err, int *ac_i)
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
