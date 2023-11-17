/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:57:27 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 13:57:29 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(int argc, char **argv, char **env)
{
	int	i;

	i = -1;
	if (!env)
		return ;
	if (argc != 1)
	{
		printf_error(1, "minishell: ft_env: too much arguments\n");
		return ;
	}
	(void)argv;
	while (env[++i])
		printf("%s\n", env[i]);
	get_infos()->latest_error_code = 0;
}
