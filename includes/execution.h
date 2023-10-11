
#ifndef EXECUTION_H
# define EXECUTION_H
# include "libftms/inc/libft.h"
# include "defines.h"
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>

/// @brief Is called when the parsing is done and it's time for the execution.
/// @param infos The t_infos structure containing the **cmd and **env.
/// @return True if success false if not.
bool	execution(t_infos *infos);

/// @brief This function dispach the command to the right place, either it's
///			a redirection or pipe or just a single command.
/// @param infos The informations structure.
void	execution_dispach(t_infos *infos);

#endif
