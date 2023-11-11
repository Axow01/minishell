
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
/// @param ac Number of arguments.
/// @param args char** arguments.
/// @param env environement variables char **.
void	cd(int ac, char **args, char **env);

/// ======== ///
///  EXPORT  ///
/// ======== ///

/// @brief Free all the value in vk
/// @param vk 
void	clean_vk(t_key_val *vk, char **cpy_env);

/// @brief Get the index of the key.
/// @param key 
/// @param env 
/// @param n 
/// @return 
int		get_env_index(char *key, char **env, size_t n);

/// @brief Prints a double char ** (used for the env).
/// @param dc char**
void	print_double_char(char **dc);

/// @brief The export command.
/// @param ac number of arguments.
/// @param argv Arguments.
/// @param env ENV.
void	ft_export(int ac, char **argv, char **env);

void	initiate_keys(char *raw_input, t_key_val *infos);

/// @brief Separate the key and the value splited on the '=' char.
/// @param raw_input A string formatted like this "$KEY=VALUE"
/// @return 
t_key_val	*export_get_key_val(char *raw_input);

/// @brief Check if the value exist in the env.
/// @param key The key to search.
/// @param env The enviroment.
/// @param n size to check.
/// @return The value or NULL if non-existant
char	*check_for_key_export(char *key, char **env, size_t n);

/// @brief Get the length of a double char pointer.
/// @param dc **char
/// @return The size of the **char.
size_t	ft_length_d_char(char **dc);

/// @brief Copy the double char **.
/// @param dc  char **.
/// @param n The size of the double char **
/// @return return the new double char.
char	**copy_double_char(char **dc, int n);

/// @brief Create a new variable in the env
/// @param vk struct
/// @param env value.
char	**create_new_variable(t_key_val *vk, char **env);

/// @brief Modify a variable in the env.
/// @param vk struct.
/// @param env value.
/// @param i the position of the value.
void	edit_variable(t_key_val *vk, char **env, int i);

/// ======== ///
///   EXIT   ///
/// ======== ///

/// @brief Exit the shell.
/// @param argc the arguements count.
/// @param argv the arguments. 
/// @param env the env (but it's not used in exit).
void	ft_exit_minishell(int argc, char **argv, char **env);

/// ========= ///
///    PWD    ///
/// ========= ///

/// @brief This is the pwd cmd.
/// @param argc 
/// @param argv 
/// @param env 
void	ft_pwd(int argc, char **argv, char **env);

/// ========== ///
///    ECHO    ///
/// ========== ///

/// @brief The fckin echo cmd
/// @param argc 
/// @param argv 
/// @param env 
void	ft_echo(int argc, char **argv, char **env);


/// ===== ///
///  ENV  ///
/// ===== ///

/// @brief The env command.
/// @param argc 
/// @param argv 
/// @param env 
void	ft_env(int argc, char **argv, char **env);

/// ======= ///
///  UNSET  ///
/// ======= ///

/// @brief The unset command.
/// @param argc 
/// @param argv 
/// @param env 
void	ft_unset(int argc, char **argv, char **env);

#endif
