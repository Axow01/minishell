
#include "../../includes/minishell.h"

bool	execution_pipe(t_infos *infos)
{
	t_pipe	*pipes;

	pipes = mms_alloc(count_cmd(&infos->cmd) - 1, sizeof(t_pipe));
	
	return (true);
}
