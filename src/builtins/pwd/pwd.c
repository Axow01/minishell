/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:02:55 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 14:02:57 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(int argc, char **argv, char **env)
{
	char	*pwd;

	(void)argv;
	(void)env;
	if (argc != 1)
	{
		printf_error(1, "minishell: ft_pwd: too many arguments\n");
		return ;
	}
	pwd = mms_alloc(PATH_MAX + 1, sizeof(char));
	getcwd(pwd, PATH_MAX + 1);
	if (pwd)
		printf("%s\n", pwd);
	mms_free(pwd);
	get_infos()->latest_error_code = 0;
}
