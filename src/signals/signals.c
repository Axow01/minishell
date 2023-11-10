
#include "../../includes/minishell.h"

void	sig_parent_handle(int signal)
{
	// char	nl_;

	// nl_ = -1;
	(void)signal;
	// write(1, "\n", 1);
	write(0, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	clean_cmd_struct(&get_infos()->cmd);
	// rl_newline('0', 0);
}

void	ft_setup_signal(int type)
{
	if (type == PARENT)
	{
		signal(SIGINT, &sig_parent_handle);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (CHILD)
	{
		signal(SIGINT, );
		signal(SIGQUIT, );
	}
	else if (HEREDOC)
	{
		signal(SIGINT, );
		signal(SIGQUIT, SIG_IGN);
	}
}
