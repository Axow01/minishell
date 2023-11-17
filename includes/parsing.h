/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:59:31 by oboucher          #+#    #+#             */
/*   Updated: 2023/11/17 13:59:34 by oboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libftms/inc/libft.h"
# define QUOTES 0
# define FNUMBER 3
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define ERROR_BASE_MSG "minishell: syntax error near unexpected token "
# define ERROR_QUOTE_MSG "minishell: syntax error quote not closed "
# define ERROR_DIR_MSG "No such file or directory"
# define BLUE "\x1b[34m"
# define LBLUE "\x1b[36;49;1;3m"
# define RED "\x1b[31m"
# define GRN "\x1b[32;1m"
# define GRY "\x1b[38;5;249m"
# define YLW "\x1b[33m"
# define RESET "\x1b[0m"
# define GIT1 "\x1b[36;49;1;3m%s\x1b[34m git:\x1b[31m(%s)"
# define GIT2 "\x1b[33m%s \x1b[32;1m[%s]\x1b[33m ➜ \x1b[0m"

void	print_cmd(t_command *lst);

//----------------------//
//       parsing        //
//----------------------//

/// @brief Main parsing function.
/// @param str The original input line.
void	parsing(char *str);

//----------------------//
//        list          //
//----------------------//

/// @brief Init all cmd node.
/// @param str The original string.
void	init_cmd_struct(char *str);

/// @brief Count how many 'char' have in original input string.
/// @param line The original input string.
/// @param delim The char.
/// @return Number of this char.
int		count_cmd_total(char *line, char delim);

//----------------------//
//        token         //
//----------------------//

/// @brief Count all none redirection.
/// @param token All token.
/// @return Then number of none redirection token.
size_t	count_nonerdt_token(char **token);

/// @brief Get all token in a cmd.
/// @param line The line.
/// @param start The start line.
/// @param end The end line.
/// @param head The struct.
void	get_token(char *line, size_t start, size_t end, t_command *head);

/// @brief Count how many token in a cmd.
/// @param line The cmd line.
/// @param start The start of that cmd line.
/// @param end The end of that cmd line.
/// @return Size_t: the number of token.
size_t	ctoken(char *line, size_t start, size_t end);

//----------------------//
//      redirection     //
//----------------------//

/// @brief Count how many redirection have in a line.
/// @param str The string.
/// @return Size_t: number of redirection.
size_t	count_redirection(char *str);

/// @brief Open fd of a command.
void	fd_maker(t_command *head);

/// @brief Check if redirection is good.
/// @param head The struct.
/// @return Bool: true if yes: false if not.
bool	check_valid_redirec(t_command *head);

/// @brief The main heredoc function.
/// @param head The node.
/// @return Bool: true if do: false if does not.
bool	heredoc(t_command *head);

/// @brief Copies the heredoc input.
/// @param delimiter The word that closes the heredoc.
/// @param fd The file descriptor for the heredoc.
/// @return Bool: Returns true if successful, false otherwise.
bool	heredoc_read(char *delimiter, int fd);

/// @brief Clean the heredoc folder.
void	heredoc_clean(void);

//----------------------//
//        prompt        //
//----------------------//

/// @brief Get the git branch name.
/// @param count return the number of folder.
/// @return Branch name.
char	*get_branch(size_t *count);

/// @brief Draw prompt.
char	*draw_prompt(size_t count);

//----------------------//
//        degit         //
//----------------------//

/// @brief Count how many degit have in a number.
/// @param n The number in long long (cast in long).
/// @return Int: how many number.
int		digit_counter(long long n);

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

/// @brief Change the $? into a error number.
/// @param new the string.
/// @param i
/// @param j
void	dollars_qmark(char *new, size_t *i, size_t *j);

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

//----------------------//
//        string        //
//----------------------//

/// @brief Count the number of a specific char.
/// @param str The string.
/// @param c The char.
/// @return Size_t the number of this char.
size_t	char_count(char *str, char c);

/// @brief Delete all specific char in a string.
/// @param str The string
/// @param c The char.
/// @return The new string without they chars and free str.
char	*ft_del_char(char *str, char c);

/// @brief Remouve coated quote.
/// @param head The struct
void	remove_quote(t_command *head);

/// @brief Remouve coated quote for one token.
/// @param token The token
/// @param new The new line.
/// @return The new line.
char	*remove_quote_token(char *token);

/// @brief Replace all space by a '\0'.
/// @param str The string.
/// @param start The start.
/// @param end The end.
void	replace_space(char *str, size_t start, size_t end);

/// @brief Print a string with all null char.
/// @param str The string.
/// @param len The string len.
void	strnput(char *str, size_t len);

/// @brief Expend the original input line.
/// @param str The original input line.
/// @param len The len of new line.
/// @return The new line.
char	*setup_line(char *str, size_t *len);

/// @brief Copy a none redirection in cmd.
/// @param head The node.
void	tmp_to_cmd(t_command *head);

/// @brief Return a copy of a char **.
char	**copy_double_char(char **dc);

#endif
