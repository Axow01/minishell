
#ifndef PARSING_H
# define PARSING_H

# include "libftms/inc/libft.h"

# define QUOTES 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

# define ERROR_BASE_MSG "minishell: syntax error near unexpected token "
# define ERROR_QUOTE_MSG "minishell: syntax error quote not closed "
# define ERROR_DIR_MSG "No such file or directory"

void	parsing(char *str);
int		count_cmd_total(char *line, char delim);
void	init_cmd_struct(char *str);
void	strnput(char *str, size_t len);
void	free_cmd(t_command *lst);
void	print_cmd(t_command *lst);

/// @brief Count how many degit have in a number.
/// @param n The number in long long (cast in long).
/// @return Int: how many number.
int	digit_counter(long long n);

//----------------------//
//          is          //
//----------------------//

/// @brief Check if a specific char is in the quote.
/// @param str The string.
/// @param pos Pos of the char in the string. (i)
/// @param quote Witch Quote (QUOTES, SINGLE_QUOTE, DOUBLE_QUOTE)
/// @return Bool: true if yes: false if not.
bool	isinquote(char *str, size_t pos, size_t quote);

/// @brief Check if the quote was a contoring quote.
/// @param str The string.
/// @param pos Pos of the char in the string. (i)
/// @return Int: 1 for >/<: 2 gor >>/<<: 0 if not.
bool	is_coated_quote(char *str, size_t pos);

/// @brief Check if the element is a redirection.
/// @param str The element.
/// @return Bool: true if yes: false if not.
int		isredirec(char *str);

/// @brief Check if redirection is valid and quote was closed.
/// @param str The string.
/// @return Bool: true if yes: false if not.
bool	is_valid(char *str);

//----------------------//
//        dollars       //
//----------------------//

/// @brief Check if the value exist in the env.
/// @param key The key to search.
/// @param env The enviroment.
/// @param n size to check.
/// @return The value or NULL if non-existant.
char	*check_for_key(char *key, char **env, size_t n);

/// @brief Check the key len before find in env.
/// @param str The char * after the $ sign.
/// @return Size_t: the len of key.
size_t	dollars_key_len(char *str);

/// @brief Check if the key exist in env.
/// @param key The key to search.
/// @param len The key len.
/// @return Bool: true if exist: false if not.
bool	dollars_key_exist(char *key, size_t len);

/// @brief Count how many valid $ sign len have in string.
/// @param str The string.
/// @return Size_t: the total len of all valid $ sign.
size_t	dollars_count(char *str);

/// @brief Copy the $ token in the new_str.
/// @param str The original string.
/// @param new_line The new string in creation.
/// @param i pos i.
/// @param j pos j.
void	dollars_token_copy(char *str, char *new_line, size_t *i, size_t *j);

#endif
