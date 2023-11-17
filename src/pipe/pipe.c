/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:04:21 by mmarcott          #+#    #+#             */
/*   Updated: 2023/11/17 14:04:22 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_unused_fd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->c_pipe[0] > 0)
		close(cmd->c_pipe[0]);
	if (cmd->previous && cmd->previous->c_pipe[1] > 0)
		close(cmd->previous->c_pipe[1]);
}

void	close_all_pipes(t_command *cmd)
{
	t_command	*buf;

	if (!cmd)
		return ;
	buf = cmd;
	while (buf)
	{
		if (buf->c_pipe[0] > 0)
			close(buf->c_pipe[0]);
		if (buf->c_pipe[1] > 0)
			close(buf->c_pipe[1]);
		buf = buf->next;
	}
}

static void	run_fork(t_command *buf, t_infos *infos)
{
	char	**env;

	ft_setup_signal(CHILD);
	close_unused_fd(buf);
	if (buf->stdout_ != STDOUT_FILENO)
		dup2(buf->stdout_, STDOUT_FILENO);
	if (buf->stdin_ != STDIN_FILENO)
		dup2(buf->stdin_, STDIN_FILENO);
	close_all_pipes(&infos->cmd);
	env = infos->env;
	if (buf->is_builtin)
	{
		((t_builtin_ptr)buf->exec_cmd)(buf->arg_count, buf->cmd_argv, env);
		mms_kill(NULL, true, 1);
	}
	untrack_cmd(buf);
	rl_clear_history();
	mms_kill(NULL, false, 0);
	mms_kill(NULL, true, execve(buf->exec_cmd, buf->cmd_argv, env));
}

static bool	run_all(t_infos *infos)
{
	t_command	*buf;

	buf = &infos->cmd;
	while (buf)
	{
		if ((buf->c_pipe[0] == 0 || buf->c_pipe[1] == 0) && buf->next)
			init_pipefd(buf);
		change_in_out(buf);
		buf->pid = fork();
		if (buf->pid == -1)
			write(STDERR_FILENO, "Failled to create forks\n", 25);
		if (buf->pid == 0)
			run_fork(buf, infos);
		if (buf->previous)
		{
			mms_close(buf->previous->c_pipe[0]);
			mms_close(buf->previous->c_pipe[1]);
		}
		buf = buf->next;
	}
	close_all_pipes(&infos->cmd);
	wait_for_programs(infos);
	return (true);
}

bool	execution_pipe(t_infos *infos)
{
	if (!init_pipefd(&infos->cmd))
		mms_kill("Pipe failled to init!\n", true, 2);
	if (!run_all(infos))
		mms_kill("Failed to execute\n", true, 2);
	return (true);
}
