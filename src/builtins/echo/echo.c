
#include "../../../includes/minishell.h"

static bool	echo_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		if (str[i] == '-' && str[i + 1] == 'n' 
				&& (str[i + 2] == ' ' || str[i + 2] == 0))
			return (false);
		i++;
	}
	return (true);
}

void	ft_echo(int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	(void)env;
	(void)argc;
	if (!echo_newline(argv[1]) && argv[1])
		i++;
	while (argv[++i])
		write(1, argv[i], ft_strlen(argv[i]));
	if (echo_newline(argv[1]))
		write(1, "\n", 1);
}
