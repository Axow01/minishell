/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:55:39 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:55:41 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_heredoc_fork(t_command *head, size_t i, char *fname)
{
	int	fd;

	rl_clear_history();
	ft_setup_signal(HEREDOC);
	fd = mms_open(fname, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (fd < 0)
		mms_kill(NULL, true, 1);
	heredoc_read(head->tmp[i + 1], fd);
	mms_close(fd);
	mms_kill(NULL, true, 0);
}

bool	heredoc_handler(t_command *head, char *fname, size_t i, int *fd)
{
	pid_t	pid;

	if (*fd > STDIN_FILENO)
		mms_close(*fd);
	get_infos()->child = true;
	pid = fork();
	if (pid == -1)
		return (false);
	else if (pid == 0)
		run_heredoc_fork(head, i, fname);
	waitpid(pid, &get_infos()->latest_error_code, 0);
	if (WEXITSTATUS(get_infos()->latest_error_code) == 28)
	{
		mms_free(fname);
		get_infos()->child = false;
		return (false);
	}
	get_infos()->child = false;
	*fd = mms_open(fname, O_RDONLY, 0);
	head->stdin_ = *fd;
	fname = mms_free(fname);
	return (true);
}

bool	heredoc(t_command *head)
{
	size_t	i;
	char	*fname;
	t_infos	*infos;
	int		fd;

	i = 0;
	fd = 0;
	infos = get_infos();
	while (head && head->tmp && head->tmp[i])
	{
		if (head->tmp[i][0] && isredirec(head->tmp[i]))
		{
			if (isredirec(head->tmp[i]) == 2 && head->tmp[i][0] == '<')
			{
				fname = ft_stringf("/tmp/heredoc%d", infos->nb_heredoc);
				infos->nb_heredoc++;
				if (!heredoc_handler(head, fname, i, &fd))
					return (false);
			}
		}
		i++;
	}
	return (true);
}
