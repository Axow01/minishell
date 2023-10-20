
#ifndef PIPE_H
# define PIPE_H

# include <defines.h>
# include <unistd.h>
# include <stdio.h>

/// @brief This complete the pipe operation for the command given.
bool	execution_pipe(t_infos *infos);

bool	init_pipefd(t_pipe *pipes);

/// @brief This function closes all the file descriptor
///				for the pipe execution function.
/// @param pipes the pipe struct.
/// @param nb_pipes  nb of pipes to clear.
void	close_all_pipes(t_pipe *pipes, int nb_pipes);

/// @brief This function waits for all the executed program to stop.
/// @param pipes The pipe structure. define.h
/// @param infos The infos structure. define.h
void	wait_for_programs(t_pipe *pipes, t_infos *infos);

/// @brief Close all except the specified ones.
/// @param pipes the pipes structure.
/// @param read the read fd.
/// @param writes the write fd.
void	close_all_except(t_pipe *pipes, int read, int writes);

/// @brief Check all in out and pipes to determine if we change
///				the in/out or no.
/// @param cmd the cmd to check (t_command struct).
/// @param pipes the pipes struct.
/// @param index the index of the command.
void	check_pipes_in_out(t_command *cmd, t_pipe *pipes, int index);

#endif
