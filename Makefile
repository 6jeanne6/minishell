################################################################################
#                          Makefile configuration                              #
################################################################################

NAME		= minishell
CFLAG		= -Wall -Wextra -g3
CC			= cc

################################################################################
#                                 Include                                      #
################################################################################

INCDIR 	 		= include
INC	   	 		= ${INCDIR}/minishell.h
INCLUDES 		= -I ${INCDIR} -I./${LIBFT_PATH}/include

################################################################################
#                                 Libft                                        #
################################################################################

LIBFT_FILE	= libft/libft.a
LIBFT_PATH	= libft/
LFLAG 		= -L./${LIBFT_PATH} -lft

################################################################################
#                                 Sources                                      #
################################################################################

SRCDIR 		= srcs

SRC			=	${SRCDIR}/main.c \
				${SRCDIR}/env/init_env.c \
				${SRCDIR}/env/env_utils.c \
				${SRCDIR}/env/find_var_name.c \
				${SRCDIR}/env/get_env_value.c \
				${SRCDIR}/env_var/init_var.c \
				${SRCDIR}/env_var/var_tools.c \
				${SRCDIR}/lexer/delimitor.c \
				${SRCDIR}/lexer/lexer_utils.c \
				${SRCDIR}/lexer/quotes.c \
				${SRCDIR}/lexer/redirections.c \
				${SRCDIR}/lexer/is_pipes.c \
				${SRCDIR}/parsing/first_parsing.c \
				${SRCDIR}/parsing/extractor.c \
				${SRCDIR}/parsing/parsing_utils.c \
				${SRCDIR}/parsing/parsing_utils2.c \
				${SRCDIR}/parsing/parsing_utils3.c \
				${SRCDIR}/parsing/tokenizer/get_token_type.c \
				${SRCDIR}/parsing/tokenizer/get_token_type_tools.c \
				${SRCDIR}/parsing/tokenizer/token_path.c \
				${SRCDIR}/parsing/tokenizer/token_order.c \
				${SRCDIR}/parsing/tokenizer/token_order_tools.c \
				${SRCDIR}/parsing/tokenizer/token_builtin.c \
				${SRCDIR}/parsing/tokenizer/token_builtin2.c \
				${SRCDIR}/parsing/tokenizer/expander.c \
				${SRCDIR}/parsing/tokenizer/expander_utils1.c \
				${SRCDIR}/parsing/tokenizer/expander_utils2.c\
				${SRCDIR}/parsing/tokenizer/expander_utils3.c\
				${SRCDIR}/execution/init_exec.c \
				${SRCDIR}/execution/init_utils.c \
				${SRCDIR}/execution/file_utils.c \
				${SRCDIR}/execution/heredoc_utils.c \
				${SRCDIR}/execution/fork_pid.c \
				${SRCDIR}/execution/child_dup.c \
				${SRCDIR}/execution/execve_all.c \
				${SRCDIR}/signals/signals.c \
				${SRCDIR}/error/error_utils.c \
				${SRCDIR}/error/free_utils.c \
				${SRCDIR}/error/pid_pipe_free.c \
				${SRCDIR}/error/close_files.c \
				${SRCDIR}/builtins/exec_builtin.c \
				${SRCDIR}/builtins/builtins_tool.c \
				${SRCDIR}/builtins/cd.c \
				${SRCDIR}/builtins/env.c \
				${SRCDIR}/builtins/exit.c \
				${SRCDIR}/builtins/pwd.c \
				${SRCDIR}/builtins/unset.c \
				${SRCDIR}/builtins/echo.c \
				${SRCDIR}/builtins/export.c \
				${SRCDIR}/debug/print_token.c \
				${SRCDIR}/status_code/update_status_code.c

################################################################################
#                                   Objects                                    #
################################################################################

OBJDIR 		= objs

OBJ    		= ${SRC:${SRCDIR}/%.c=${OBJDIR}/%.o}

################################################################################
#                                   Colors                                     #
################################################################################

BLACK 	= \033[0;30m
RED 	= \033[0;31m
GREEN 	= \033[0;32m
YELLOW 	= \033[0;33m
BLUE 	= \033[0;34m
PURPLE 	= \033[0;35m
CYAN 	= \033[0;36m

################################################################################
#                                    Rules                                     #
################################################################################

all: ${LIBFT_FILE} ${NAME}

${NAME} : ${OBJ} 
	@${CC} ${CFLAG} ${INCLUDES} ${OBJ} ${LFLAG} -o ${NAME} -lreadline
	@echo "${YELLOW}✰✰✰ Alright, you can use ${NAME} ✰✰✰ :D"

${OBJDIR}/%.o: ${SRCDIR}/%.c ${INC}
	@mkdir -p ${dir $@}
	@${CC} ${CFLAG} ${INCLUDES} -c $< -o $@
	@echo "${GREEN}***  MINISHELL: compilation success  ***"

${LIBFT_FILE} :
	@make -sC libft

clean: 
	@rm -rf ${OBJDIR}
	@echo "${PURPLE}► Cleaning done: ${OBJDIR} directory has been removed ◄"
	@make clean -C ${LIBFT_PATH}

fclean: clean
	@rm -f ${NAME} ${NAME_BONUS}
	@echo "${BLUE}► Fclean done: ${NAME} and ${NAME_BONUS} has been removed ◄"
	@make fclean -C ${LIBFT_PATH}

re: fclean all
	@echo "${CYAN}↻↻↻ Makefile has been re'd ↺↺↺ \o/"

.PHONY: all clean fclean re bonus
