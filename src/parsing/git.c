#include "minishell.h"


static char *find_git(size_t *count)
{
	char	*git_dir;

    git_dir = ft_strdup(".git/HEAD");
	while (access(git_dir, F_OK) != 0 && char_count(git_dir,
			'/') < char_count(get_infos()->pwd, '/'))
		git_dir = ft_stringf("%s%s", "../", git_dir);
    if (access(git_dir, F_OK) == 0)
    {
        *count = char_count(git_dir,'/') - 1;
		printf("%zu\n", *count);
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
		fd = open(git_dir, O_RDONLY);
		temp = get_next_line(fd);
		i = ft_strlen(temp) - 1;
		while (temp[i] && temp[i] != '/')
			i--;
		new = ft_del_char(ft_strdup(&temp[i + 1]), '\n');
		mms_free(temp);
		mms_free(git_dir);
		close(fd);
		return (new);
	}
	return (NULL);
}

char *draw_prompt(size_t count)
{
    char *new;
    char *cursor;
	t_infos	*infos;
    size_t i;

    i = 0;
    cursor = ft_strdup("➜");
    while (i < count)
    {
        cursor = ft_stringf("%s%s", cursor, "➜");
        i++;
    }
	infos = get_infos();
    new = NULL;
    if (!infos->git_branch || infos->git_branch[0] == '\0')
        new = ft_stringf(LBLUE"%s"YLW " ~ " GRY RESET, infos->pwd);
    else
    {
		new = ft_stringf(LBLUE"%s"BLUE " git:" RED "(%s)" YLW "%s "GRY RESET, infos->pwd, infos->git_branch, cursor);
    }
    return (new);
}