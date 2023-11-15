
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

static void	update_pwd_env(char *pwd, t_infos *infos, char *old_pwd)
{
	char	*args[3];

	args[0] = ft_stringf("export");
	args[1] = ft_stringf("PWD=%s", pwd);
	args[2] = NULL;
	ft_export(2, args, infos->env);
	mms_free(args[1]);
	args[1] = ft_stringf("OLDPWD=%s", old_pwd);
	ft_export(2, args, infos->env);
	mms_free(args[0]);
	mms_free(args[1]);
}

void	finish_cd_process(char *pwd, char *current_dir, char *old_pwd)
{
	if (!pwd)
	{
		printf_error(1, "minishell: cd: HOME variable not set\n");
		return ;
	}
	if (chdir(pwd) != 0)
	{
		printf_error(1, "minishell: cd: No such file or directory\n");
		mms_free(pwd);
		return ;
	}
	old_pwd = ft_strdup(current_dir);
	getcwd(current_dir, PATH_MAX);
	update_pwd_env(current_dir, get_infos(), old_pwd);
	mms_free(pwd);
}

void	cd(int ac, char **args, char **env)
{
	char	*pwd;
	char	*home_dir;
	char	*old_pwd;
	char	current_dir[PATH_MAX];

	if (!args || ac == 0 || !env)
		return ;
	home_dir = check_for_key("HOME", env, 4);
	old_pwd = check_for_key("OLDPWD", env, 6);
	pwd = NULL;
	getcwd(current_dir, PATH_MAX);
	if (ac == 1 || !args[1])
		pwd = home_dir;
	else if (ac > 1 && args[1][0] == '-')
	{
		pwd = old_pwd;
		printf("%s\n", pwd);
	}
	else if (check_path_type(&args[1]) == ABSOLUTE_PATH)
		pwd = args[1];
	else
		pwd = new_path(current_dir, args[1]);
	finish_cd_process(pwd, current_dir, old_pwd);
}
