#ifndef PIPE_H
# define PIPE_H

# include <defines.h>
# include <stdio.h>
# include <unistd.h>

/// @brief This complete the pipe operation for the command given.
bool	execution_pipe(t_infos *infos);

/// @brief This function check the validity of a command.
/// @param cmd node to check.
/// @return True if the command is valid, false if not.
bool	check_cmd_valid(t_command *cmd);

/// @brief This initiate the pipes of the current and previous command.
/// @param cmd node to do the action on.
/// @return True if successful, false if not.
bool	init_pipefd(t_command *cmd);

/// @brief This function waits for each fork to finish.
/// @param infos structure.
void	wait_for_programs(t_infos *infos);

/// @brief Change the cmd stdin/out if needed.
/// @param cmd
void	change_in_out(t_command *cmd);

/// @brief Close all the pipes.
/// @param cmd cmd struct.
void	close_all_pipes(t_command *cmd);

/// @brief Verif the pipes, for error. Fd in out etc...
/// @param infos 
/// @param buf 
void	pipe_fork_verif(t_infos *infos, t_command *buf);

#endif
