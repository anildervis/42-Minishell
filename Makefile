NAME			=	minishell
OBJ_DIR			=	obj/
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g
RM				=	rm -f
READLINE		=	-lreadline


BUILTIN_DIR		=	builtin/
BUILTIN_FILES	=	builtin cd echo env exit export pwd unset
BUSINESS_DIR	=	business/
BUSINESS_FILES	=	executor expander lexer main parser
ERROR_DIR		=	err/
ERROR_FILES		=	err
FREE_DIR		=	free/
FREE_FILES		=	free
UTILS_DIR		=	utils/
UTILS_FILES		=	find_pair ft_atoi ft_bzero ft_calloc ft_itoa ft_split ft_strcmp ft_strchr ft_strdup ft_strjoin ft_strlcpy ft_strlen ft_strncmp ft_strnsearch ft_strnstr ft_substr get_env get_path is_parent is_whitespace key_val list_len set_env set_path

B_FILES			=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES))
BS_FILES		=	$(addprefix $(BUSINESS_DIR), $(BUSINESS_FILES))
E_FILES			=	$(addprefix $(ERROR_DIR), $(ERROR_FILES))
F_FIlES			=	$(addprefix $(FREE_DIR), $(FREE_FILES))
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

all:				$(NAME)

$(NAME):			$(OBJF) $(BOBJ) $(BSOBJ) $(EOBJ) $(FOBJ) $(UOBJ)
					@$(CC) $(CFLAGS) $(BOBJ) $(BSOBJ) $(EOBJ) $(FOBJ) $(UOBJ) -o $(NAME) $(READLINE)

$(OBJ_DIR)%.o:		$(BUILTIN_DIR)%.c $(BUSINESS_DIR)%.c $(ERROR_DIR)%.c $(FREE_DIR)%.c $(UTILS_DIR)%.c $(OBJF)
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
					@$(RM) -r $(OBJ_DIR)
					@$(RM) $(OBJF)

fclean:				clean
					@$(RM) $(NAME)
					@rm -rf *.dSYM
					@find . -name ".DS_Store" -delete

re:					fclean all

.PHONY:				all clean fclean re
