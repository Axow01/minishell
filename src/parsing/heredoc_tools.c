/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:55:34 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:55:36 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_parsing(char *line, bool do_dollar)
{
	size_t	i;
	size_t	j;
	char	*new;

	new = NULL;
	if (do_dollar)
		new = mms_alloc(ft_strlen(line) + dollars_count(line) + 1,
				sizeof(char));
	else
		new = mms_alloc(ft_strlen(line) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (do_dollar && line[i] == '$')
			dollars_token_copy(line, new, &i, &j);
		if (line[i])
			new[j++] = line[i++];
	}
	mms_free(line);
	return (new);
}

bool	delimiter_isinquote(char *delimiter, bool do_dollar)
{
	if (char_count(delimiter, '"') > 0 || char_count(delimiter, '\'') > 0)
	{
		do_dollar = false;
		delimiter = remove_quote_token(delimiter);
	}
	else
		do_dollar = true;
	return (do_dollar);
}

bool	heredoc_read(char *delimiter, int fd)
{
	char	*line;
	char	*new;
	bool	do_dollar;

	do_dollar = false;
	do_dollar = delimiter_isinquote(delimiter, do_dollar);
	delimiter = remove_quote_token(delimiter);
	while (true)
	{
		line = readline("heredoc> ");
		if (!line)
			return (false);
		mms_add_ptr(line);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
			return (false);
		new = heredoc_parsing(line, do_dollar);
		if (!new)
			return (false);
		ft_putendl_fd(new, fd);
		line = mms_free(line);
		mms_free(new);
	}
	return (true);
}

void	heredoc_clean(void)
{
	int		i;
	char	*fname;

	i = get_infos()->nb_heredoc;
	while (i >= 0)
	{
		fname = ft_stringf("%s%s%d", "/tmp", "/heredoc", i);
		unlink(fname);
		fname = mms_free(fname);
		i--;
	}
}
