
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

#endif
