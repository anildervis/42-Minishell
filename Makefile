NAME			=	minishell
OBJ_DIR			=	obj/
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -rf
READLINE		=	-lreadline
LIB				=	minishell.h

SUCCESS			=	@echo "\033[32mSuccessfull !\033[0m"
CLEANED			=	@echo "\033[34mCleaned !\033[0m"

BUILTIN_DIR		=	builtin/
BUILTIN_FILES	=	builtin cd echo env exit export pwd unset
BUSINESS_DIR	=	business/
BUSINESS_FILES	=	executor expander lexer main parser syntax_check_helper find_token_helper parser_helper \
					add_type file_descriptors executor_helper wildcard add_wildcards syntax_check
ERROR_DIR		=	err/
ERROR_FILES		=	err
FREE_DIR		=	free/
FREE_FILES		=	free
UTILS_DIR		=	utils/
UTILS_FILES		=	find_pair ft_atoi ft_bzero ft_calloc ft_itoa ft_split ft_strcmp \
					ft_strchr ft_strdup ft_strjoin ft_strlcpy ft_strlen ft_strncmp  \
					ft_strnsearch ft_substr get_env get_path is_whitespace new_token  \
					list_len set_env set_paths strnstr_wildcard is_metachar         \
					t_str_lexer ft_is_redirect ft_strcpy set_current_pwd set_old_pwd

B_FILES			=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES))
BS_FILES		=	$(addprefix $(BUSINESS_DIR), $(BUSINESS_FILES))
E_FILES			=	$(addprefix $(ERROR_DIR), $(ERROR_FILES))
F_FILES			=	$(addprefix $(FREE_DIR), $(FREE_FILES))
U_FILES			=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))

BUILTIN			=	$(addsuffix .c, $(B_FILES))
BOBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(B_FILES)))

BUSINESS		=	$(addsuffix .c, $(BS_FILES))
BSOBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(BS_FILES)))

ERROR			=	$(addsuffix .c, $(E_FILES))
EOBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(E_FILES)))

FREE			=	$(addsuffix .c, $(F_FILES))
FOBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(F_FILES)))

UTILS			=	$(addsuffix .c, $(U_FILES))
UOBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(U_FILES)))

OBJF			=	.cache_exists

all:				$(NAME) $(LIB)

$(NAME):			$(OBJF) $(BOBJ) $(BSOBJ) $(EOBJ) $(FOBJ) $(UOBJ)
					@$(CC) $(CFLAGS) $(BOBJ) $(BSOBJ) $(EOBJ) $(FOBJ) $(UOBJ) $(READLINE) -o $(NAME)
					$(SUCCESS)

$(OBJ_DIR)%.o:		%.c
					@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
					@mkdir -p $(OBJ_DIR)
					@mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)
					@mkdir -p $(OBJ_DIR)$(BUSINESS_DIR)
					@mkdir -p $(OBJ_DIR)$(ERROR_DIR)
					@mkdir -p $(OBJ_DIR)$(FREE_DIR)
					@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
					@touch $(OBJF)

clean:
					@$(RM) $(OBJ_DIR)
					@$(RM) $(OBJF)
					$(CLEANED)

fclean:				clean
					@$(RM) $(NAME)
					@$(RM) *.dSYM
					@find . -name ".DS_Store" -delete

re:					fclean all

.PHONY:				all clean fclean re
