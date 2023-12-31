#include "../../../includes/minishell.h"

static bool	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

void	ft_exit_minishell(int argc, char **argv, char **env)
{
	int	n;

	(void)env;
	if (argc == 1)
		mms_kill(NULL, true, get_infos()->latest_error_code);
	if (!is_num(argv[1]))
	{
		printf_error(1, "minishell: ft_exit: The argument n:%s seems wrong\n",
			argv[1]);
		return ;
	}
	n = ft_atoi(argv[1]);
	mms_kill(NULL, true, (unsigned char)n);
}
