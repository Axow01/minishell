
#include "../../includes/minishell.h"

bool	execution_pipe(t_infos *infos)
{
	int			pipefd[2];
	char		*buf;
	pid_t		pid;

	buf = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("Pipe error!\n");
		return (false);
	}
	pid = fork();
	if (pid == 0) // Child process.
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (execve(, NULL, infos->env) == -1)
			perror("Exec fail!\n");
	}
	else // Parent process.
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);

		free(buf);
		close(pipefd[0]);
	}
	return (true);
}
