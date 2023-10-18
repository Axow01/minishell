
#ifndef PIPE_H
# define PIPE_H

# include <defines.h>
# include <unistd.h>
# include <stdio.h>

/// @brief This complete the pipe operation for the command given.
/// @param  
/// @return 
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

#endif
