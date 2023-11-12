
#ifndef EXECUTION_H
# define EXECUTION_H
# include "defines.h"
# include "libftms/inc/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>

/// @brief Is called when the parsing is done and it's time for the execution.
/// @param infos The t_infos structure containing the **cmd and **env.
/// @return True if success false if not.
bool			execution(t_infos *infos);

/// @brief This function dispach the command to the right place, either it's
///			a redirection or pipe or just a single command.
/// @param infos The informations structure.
void			execution_dispach(t_infos *infos);

/// @brief This function return the type of the path.
//				(absolute or command from the environement).
/// @param cmd The cmd double char pointer.
/// @return The right path type.
t_path			check_path_type(char **cmd);

int16_t			count_cmd(t_command *cmd);

/// @brief This execute the command.
/// @param cmd the cmd to run.
/// @return true if success false if not.
bool			simple_exec(t_command *cmd);

/// @brief This remove the nessecary values from libmms tracking.
/// @param cmd struct.
void			untrack_cmd(t_command *cmd);

/// @brief Checks for builtins, and if found run the function of the builtins.
/// @param cmd structure.
bool			check_for_builtins(t_command *cmd);

/// @brief Clean struct.
void			clean_cmd_struct(t_command *cmd);

/// @brief Returns the builtin function pointer.
/// @param cmd
/// @return func ptr
t_builtin_ptr	get_builtin_ptr(t_command *cmd);

/// @brief Config de builtins.
/// @param cmd_buffer
/// @param infos
void			config_builtins_cmd(t_command *cmd_buffer, t_infos *infos);

#endif
