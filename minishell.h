#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/wait.h>

#define DOUBLE_QUOTE "\""
#define SINGLE_QUOTE "'"
#define DOLLAR_SIGN "$"
#define WILD_CARD "*"
#define QUESTION_MARK "?"
#define BRACETS "{}"
#define SLASH "/"
#define READ_END 0
#define WRITE_END 1

#define ESLASH 1 // Komutun slash karakteri içerdiği hata kodu
#define EADDPATH 2 // Path eklerken oluşan hata kodu
#define EPWD 3 // Getcwd fonksiyonu çalışmazsa oluşacak hata kodu
#define ECD 4 // Chdir fonksiyonu çalışmazsa oluşacak hata kodu

enum e_builtin_types
{
	CD = 1,
	ENV,
	PWD,
	ECHO,
	EXIT,
	UNSET,
	EXPORT
};

enum tokens{
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_GREATER,
	TOKEN_SMALLER,
	TOKEN_APPEND,
	TOKEN_HERE_DOC,
	TOKEN_OPEN_PAR,
	TOKEN_CLOSE_PAR,
	TOKEN_STR
};

enum errors{
	FILE_NOT_FOUND = 1,
	SYNTAX_ERROR = 2,
	PERM_DENIED = 4,
	CMD_NOT_FOUND = 127,
	SYSTEM_ERR = -1,
	MEMORY_ERR = -2,
	DUP_ERR = -3,
	FORK_ERR = -4,
	PIPE_ERR = -5
};

typedef struct s_token
{
	enum tokens		type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_file
{
	enum tokens		type;
	char			*file_name;
	struct s_file	*next;
}					t_file;

typedef struct	s_ms
{
	int			ignore;
	int			opening_prompt;
	int			parent_pid;
	int			*child_pids;
	int			child_pids_count;
	int			in_file;
	int			out_file;
	char		**ev;
	char		**paths;
}				t_ms;

typedef struct s_parsed
{
	int			exec;
	int			in_file;
	int			out_file;
	char		*cmd;
	char		**arguments;
	t_token		*paranthesis;
	struct s_parsed	**parantheses_andor;
	t_file		*file_list;
	struct s_parsed	*prev;
	struct s_parsed	*next;
}				t_parsed;

extern t_ms	g_ms;

// utils
char	*ft_strdup(const char *str);
void	init_ms(char **ev);
char	*get_env(char *str);
void	check_dir(char *cmd);
char	*get_path(char *cmd);
int		addenv(char *key, char *val);
int		is_whitespace(char c);
char	**set_ev(char **ev);
int		env_len(void);
void	set_paths(void);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*strnstr_wildcard(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		find_pair(char *input, char c);
int		list_len(char **char_list);
int		ft_strnsearch(char *string, char *chars_to_search, size_t len);
int		is_metacharacter(char c);
int		token_str_lexer(char *input);
t_token	*new_token(enum tokens type, char *value);

//error
// void	cmd_err(char *str);
// void	no_file_err(char *str);
int		print_error(int error_code, char *param);

//free
void	free_array(char **arr);

//builtin
int		is_builtin(char *command);
void	run_builtin(char **exe);
void	builtin_cd(char **execute);
void	builtin_echo(char **input);
void	builtin_env(void);
void	builtin_exit(char **input);
void	builtin_export(char **input);
void	builtin_pwd(void);
void	builtin_unset(char **input);

//--------------lexer--------------
int			is_metacharacter(char c);
int			token_str_lexer(char *input);
int			add_token(char *input, t_token *command_table, enum tokens type, int len);
void		find_token(char *input, t_token *command_table);
t_token		*tokenizer(char *input);
void		get_next_token(t_token *command_table);
int			syntax_check(t_token *command_table);
int			init_token(char *input, t_token *command_table);
int			init_token_continue(char *input, t_token *command_table);

//--------------expander--------------
int			add_double_quote(char **str, char *val);
int			add_single_quote(char **str, char *val);
int			add_dollar(char **str, char *val);
int			add_char(char **str, char *val);
char		*check_str(char *value);
int			wild_path(char *wild_one, char *expected_one);
void		wildcard(char *path, char **destined_path, int way, char ***arguments);
void		add_wildcard_to_list(char *path, char ***arguments);
void		expander(t_parsed **command);

//--------------parser--------------
int			andor_count(t_token *command_table);
t_parsed	*new_parse_command(int in_file, int out_file);
void		add_andor_list(t_parsed *command, t_parsed **andor_table);
void		add_redirection(t_token **command_table, t_parsed **command);
void		skip_paranthesis(t_token **command_table);
t_parsed	*add_parse(t_token **command_table, t_parsed **old_command);
void		add_argument(t_token **command_table, t_parsed **command);
void		add_paranthesis(t_token **command_table, t_parsed **command);
t_parsed	**parse_commands(int in_file, int out_file, t_token *command_table);

//--------------executor--------------
void		close_fd(t_parsed *command);
int			here_doc_fd(char *limiter);
int			read_file_fd(char *file_name, int type);
int			write_file_fd(char *file_name, int type);
void		apply_redirection(t_parsed **command);
void		child_organizer(t_parsed *command);
void		command_executor(t_parsed *command);
void		create_pipe(t_parsed **command);
void		create_redirections(t_parsed **andor_table);
void		organizer(t_parsed **andor_table);
void		executor(t_parsed **andor_table);

//------------token_checker-------------
int			ft_token_checker(t_token *tmp, int *p_count);
int			ft_token_sgha(t_token *tmp, int *p_count);
int			ft_token_paoc(t_token *tmp);
#endif
