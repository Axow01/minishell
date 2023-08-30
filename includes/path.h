
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

#endif
