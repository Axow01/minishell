#include "../../../includes/minishell.h"

static bool	echo_newline(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (false);
	}
	return (true);
}

int	echo_newline_count(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (echo_newline(argv[i]))
			break ;
		i++;
	}
	return (i - 1);
}

void	ft_echo(int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	(void)env;
	if (argv[1] && !echo_newline(argv[1]))
		i = echo_newline_count(argv);
	while (argv[++i])
	{
		if (i != argc - 1)
		{
			ft_putstr_fd(argv[i], 1);
			ft_putchar_fd(' ', 1);
		}
		else
			ft_putstr_fd(argv[i], 1);
	}
	if (echo_newline(argv[1]))
		ft_putchar_fd('\n', 1);
	get_infos()->latest_error_code = 0;
}
