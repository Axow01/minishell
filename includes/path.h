
#ifndef PATH_H
# define PATH_H

# include <stdbool.h>

/// @brief Transform the env** variable to the path value only.
/// @param env The environement variable.
/// @return path (char*).
char	*env_to_path(char **env);

/// @brief Splits the path variable into a double array.
/// @param path the path string.
/// @return path_splited (char**).
char	**path_split(char *path);

/// @brief This check the path from the environement if the program exist in it.
/// @param cmd the command to verify.
/// @param path the path from the environement.
/// @return The absolute path of the program if found, otherwise return's NULL.
char	*get_cmd_path(char **cmd, char **path);

/// @brief This gets the current directory of the shell.
/// @param env the environements variables.
/// @return The pwd (char *).
char	*get_pwd(char **env);

#endif
