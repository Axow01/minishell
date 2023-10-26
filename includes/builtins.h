
#ifndef BUILTINS_H
# define BUILTINS_H


typedef struct s_key_val
{
	char	*key;
	char	*value;
}		t_key_val;

/// ==== ///
///  CD  ///
/// ==== ///

/// @brief This is the cd function this changes the current directory.
/// @param new_path The new directory to go.
/// @param env The env variable.
void	cd(char *new_path, char **env);

/// ======== ///
///  EXPORT  ///
/// ======== ///

/// @brief Prints a double char ** (used for the env).
/// @param dc char**
void	print_double_char(char **dc);

/// @brief The export command.
/// @param ac number of arguments.
/// @param argv Arguments.
/// @param env ENV.
/// @return the new env.
char	**ft_export(int ac, char **argv, char **env);

/// @brief Separate the key and the value splited on the '=' char.
/// @param raw_input A string formatted like this "$KEY=VALUE"
/// @return 
t_key_val	*export_get_key_val(char *raw_input);

/// @brief Check if the value exist in the env.
/// @param key The key to search.
/// @param env The enviroment.
/// @param n size to check.
/// @return The value or NULL if non-existant
char	*check_for_key(char *key, char **env, size_t n);

#endif
