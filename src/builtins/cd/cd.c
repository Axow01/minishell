
#include "../../../includes/minishell.h"

static char	*new_path(char *current, char *addition)
{
	char	*pwd;
	int		i;
	int		k;

	if (!current || !addition)
		return (NULL);
	i = -1;
	k = -1;
	pwd = mms_alloc(ft_strlen(current) + ft_strlen(addition) + 2, sizeof(char));
	while (current[++i])
		pwd[i] = current[i];
	pwd[i++] = '/';
	while (addition[++k])
		pwd[i++] = addition[k];
	return (pwd);
}

static void	update_pwd_env(char *pwd, t_infos *infos)
{
	char	*args[3];

	args[0] = ft_stringf("export");
	args[1] = ft_stringf("PWD=%s", pwd);
	args[2] = NULL;
	ft_export(2, args, infos->env);
	mms_free(args[0]);
	mms_free(args[1]);
}

void	cd(int ac, char **args, char **env)
{
	char	*pwd;
	char	*home_dir;
	char	current_dir[PATH_MAX];

	if (!args || ac == 0 || !env)
		return ;
	home_dir = check_for_key("HOME", env, 4);
	pwd = NULL;
	getcwd(current_dir, PATH_MAX);
	if (ac == 1 || !args[1])
		pwd = home_dir;
	else if (check_path_type(&args[1]) == ABSOLUTE_PATH)
		pwd = args[1];
	else
		pwd = new_path(current_dir, args[1]);
	if (chdir(pwd) != 0)
		printf_error("minishell: cd: No such file or directory\n");
	getcwd(current_dir, PATH_MAX);
	update_pwd_env(current_dir, get_infos());
	mms_free(pwd);
}
