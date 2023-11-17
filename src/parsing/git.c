/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:55:29 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:55:31 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_git(size_t *count)
{
	char	*git_dir;

	git_dir = ft_strdup(".git/HEAD");
	while (access(git_dir, F_OK) != 0 && char_count(git_dir,
			'/') < char_count(get_infos()->pwd, '/'))
		git_dir = ft_stringf("%s%S", "../", git_dir);
	if (access(git_dir, F_OK) == 0)
	{
		*count = char_count(git_dir, '/') - 1;
		return (git_dir);
	}
	return (NULL);
}

char	*get_branch(size_t *count)
{
	char	*git_dir;
	char	*new;
	char	*temp;
	int		fd;
	size_t	i;

	fd = 0;
	git_dir = find_git(count);
	if (git_dir && access(git_dir, F_OK) == 0)
	{
		fd = mms_open(git_dir, O_RDONLY, 0);
		temp = get_next_line(fd);
		i = ft_strlen(temp) - 1;
		while (temp[i] && temp[i] != '/')
			i--;
		new = ft_del_char(ft_strdup(&temp[i + 1]), '\n');
		mms_free(temp);
		mms_free(git_dir);
		mms_close(fd);
		return (new);
	}
	return (NULL);
}

size_t	pwd_trim(char *pwd, size_t nb)
{
	size_t	i;
	size_t	count;

	i = ft_strlen(pwd);
	count = 0;
	while (i > 0)
	{
		if (pwd[i] == '/')
			count++;
		if (count == nb)
		{
			if (i > 0)
				i++;
			break ;
		}
		i--;
	}
	return (i);
}

char	*draw_prompt(size_t count)
{
	char	*new;
	char	*cursor;
	t_infos	*infos;
	size_t	i;

	i = 0;
	cursor = ft_strdup("❯");
	while (i < count)
	{
		cursor = ft_stringf("%S%s", cursor, "❯");
		i++;
	}
	infos = get_infos();
	new = NULL;
	if (!infos->git_branch || infos->git_branch[0] == '\0')
		new = ft_stringf(LBLUE "%s" GRN " [%s] " YLW "➜ " RESET,
				&infos->pwd[pwd_trim(infos->pwd, FNUMBER)], infos->username);
	else
	{
		new = ft_stringf(GIT1 GIT2, &infos->pwd[pwd_trim(infos->pwd, FNUMBER)],
				infos->git_branch, cursor, infos->username);
	}
	return (new);
}
