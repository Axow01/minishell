/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:59:48 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:59:50 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#endif
