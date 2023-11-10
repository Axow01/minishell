
#include "../../includes/minishell.h"

void	sig_parent_handle(int signal)
{
	(void)signal;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	clean_cmd_struct(&get_infos()->cmd);
}

void	ft_setup_signal(int type)
{
	if (type == PARENT)
	{
		signal(SIGINT, &sig_parent_handle);
		signal(SIGQUIT, SIG_IGN);
	}
	// else if (CHILD)
	// {
	// 	signal(SIGINT, );
	// 	signal(SIGQUIT, );
	// }
	// else if (HEREDOC)
	// {
	// 	signal(SIGINT, );
	// 	signal(SIGQUIT, SIG_IGN);
	// }
}
