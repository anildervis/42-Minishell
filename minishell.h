#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>

#define DOUBLE_QUOTE = "\""
#define SINGLE_QUOTE = "\'"
#define DOLLAR_SIGN = "$"
#define WILD_CARD = "*"
#define QUESTION_MARK = "?"
#define BRACETS = "{}"
#define SLASH = "/"

typedef struct	s_ms
{
	int			pid;
	int			error_status;
	char		**ev;
	char		**path;
}				t_ms;

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
}

typedef struct s_token
{
	enum tokens	*type;
	char	*value;
	t_token	*prev;
	t_token *next;
}				t_token;

//utils
int		ft_strlen(const char *str);
char	*ft_strdup(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
int		find_pair(char *input, char c);

//--------------tokenizer--------------
int add_token(char *input, t_token **command_table, enum tokens type, int len);
t_token **find_token(char *input, t_token **command_table);
t_token *tokenizer(char *input);

#endif
