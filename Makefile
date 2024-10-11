NAME	=	minishell

LIB		=	./src/libft/libft_bonus.a

HEADER	=	./includes/minishell.h

PARS	=	garbage_collector.c utils.c tokenizer.c parser.c \
			parsing_utils.c constructor_functions.c expander.c \
			validator.c handle_signals.c tokenizer_utils.c expander_utils.c \
			parser_additional.c wildcard.c tokenizer_utils1.c \
			constructor_functions_additional.c expander_utils2.c \
			heredoc_functions.c wildcard_utils.c validator_additional.c \
			expander_utils3.c remove_invalid_variables.c \
			expand_cmd_variables.c expander_utils4.c

EXEC	=	runcmd.c execution.c redirection.c heredoc.c pipe.c logop.c \
			builtins/cd.c builtins/change_pwd.c builtins/echo.c builtins/env.c \
			builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c \
			execute_subshell_block.c execution_utils.c builtins/export_utils.c \
			builtins/export_utils1.c

UTILS	=	end_process.c cm_strdup.c ft_dblptrlen.c strjoin.c ft_strncpy.c \
			ft_strndup.c strsplit.c substr.c safe_fork.c \
			get_copy_with_malloc.c compare_variables.c ft_getenv.c cm_itoa.c \
			ft_isspace.c cm_strstr.c remove_trailing_whitespaces.c split.c \
			split_argument.c isreturning.c


GNL		=	get_next_line.c get_next_line_utils.c

SRC		=	src/main.c src/minishell.c $(addprefix src/parsing/,${PARS}) \
			$(addprefix src/execution/,${EXEC}) \
			$(addprefix src/get_next_line/, ${GNL}) \
			$(addprefix src/utils/, ${UTILS})

OBJS	=	${SRC:.c=.o}

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
MFLAGS	=	-Lsrc/libft -lft_bonus -lreadline

RM		=	rm -f

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -Iincludes -c $< -o $@

${NAME}: ${OBJS} ${HEADER} ${LIB}
	${CC} ${CFLAGS} ${OBJS} ${MFLAGS} -o ${NAME}

${LIB}:
	@${MAKE} -C src/libft bonus --quiet

clean:
	${RM} ${OBJS}
	@${MAKE} -C src/libft clean --quiet

fclean:	clean
	${RM} ${NAME}
	@${MAKE} -C src/libft fclean --quiet

re:	fclean all

.PHONY: all clean fclean re
.SECONDARY:	${OBJS}
