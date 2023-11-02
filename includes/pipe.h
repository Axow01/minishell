
#ifndef PIPE_H
# define PIPE_H

# include <defines.h>
# include <unistd.h>
# include <stdio.h>

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

#endif
