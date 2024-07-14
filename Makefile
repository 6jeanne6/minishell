################################################################################
#                          Makefile configuration                              #
################################################################################

NAME		= minishell
CFLAG		= -Wall -Wextra -Werror -g3
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
				${SRCDIR}/env/env.c \
				${SRCDIR}/env/env_utils.c \
				${SRCDIR}/lexer/lexer.c \
				${SRCDIR}/lexer/lex_redirections.c \
				${SRCDIR}/lexer/lexer_utils.c \
				${SRCDIR}/signals/signals.c \
				${SRCDIR}/error/error_utils.c \

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
