
#include "../../includes/minishell.h"

void	sig_parent_handle(int signal)
{
	(void)signal;
	if (get_infos()->child)
		return ;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	clean_cmd_struct(&get_infos()->cmd);
}

void	sig_child_handle(int signal)
{
	(void)signal;
	mms_kill(NULL, true, 1);
}

void	sig_heredoc_handle(int signal)
{
	(void)signal;
	mms_kill("\n", true, 28);
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
		signal(SIGINT, &sig_child_handle);
		signal(SIGQUIT, &sig_child_handle);
	}
	else if (HEREDOC)
	{
		signal(SIGINT, &sig_heredoc_handle);
		signal(SIGQUIT, SIG_IGN);
	}
}
