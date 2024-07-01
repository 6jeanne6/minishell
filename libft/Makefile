################################################################################
#                          Makefile configuration                              #
################################################################################

NAME	= libft.a
AR		= ar -crs
CFLAG	= -Wall -Wextra -Werror -g3
CC		= cc

################################################################################
#                                 Include                                      #
################################################################################

INCDIR 	= include

INC		= ${INCDIR}/libft.h \
	  	  ${INCDIR}/ft_printf.h \
	  	  ${INCDIR}/get_next_line.h \
	  	  ${INCDIR}/get_next_line_bonus.h \

################################################################################
#                                 Sources                              	       #
################################################################################

SRCDIR 		= src

FT_IS		= ${SRCDIR}/ft_is/ft_isalnum.c \
		  	  ${SRCDIR}/ft_is/ft_isalpha.c \
		  	  ${SRCDIR}/ft_is/ft_isascii.c \
		  	  ${SRCDIR}/ft_is/ft_isdigit.c \
		  	  ${SRCDIR}/ft_is/ft_isprint.c \

FT_LST		= ${SRCDIR}/ft_lst/ft_lstadd_back.c \
		  	  ${SRCDIR}/ft_lst/ft_lstadd_front.c \
		  	  ${SRCDIR}/ft_lst/ft_lstclear.c \
		  	  ${SRCDIR}/ft_lst/ft_lstdelone.c \
		  	  ${SRCDIR}/ft_lst/ft_lstiter.c \
		  	  ${SRCDIR}/ft_lst/ft_lstlast.c \
		  	  ${SRCDIR}/ft_lst/ft_lstmap.c \
		  	  ${SRCDIR}/ft_lst/ft_lstnew.c \
		  	  ${SRCDIR}/ft_lst/ft_lstsize.c \

FT_STR		= ${SRCDIR}/ft_str/ft_strchr.c \
			  ${SRCDIR}/ft_str/ft_strcmp.c \
		  	  ${SRCDIR}/ft_str/ft_strdup.c \
		  	  ${SRCDIR}/ft_str/ft_striteri.c \
		  	  ${SRCDIR}/ft_str/ft_strjoin.c \
		  	  ${SRCDIR}/ft_str/ft_strlcat.c \
		  	  ${SRCDIR}/ft_str/ft_strlcpy.c \
		  	  ${SRCDIR}/ft_str/ft_strlen.c \
		  	  ${SRCDIR}/ft_str/ft_strmapi.c \
		  	  ${SRCDIR}/ft_str/ft_strncmp.c \
		  	  ${SRCDIR}/ft_str/ft_strnstr.c \
		  	  ${SRCDIR}/ft_str/ft_strrchr.c \
		  	  ${SRCDIR}/ft_str/ft_strtrim.c \
		  	  ${SRCDIR}/ft_str/ft_substr.c \
		  	  ${SRCDIR}/ft_str/ft_strstr.c \

FT_FD		= ${SRCDIR}/ft_fd/ft_putchar_fd.c \
		  	  ${SRCDIR}/ft_fd/ft_putendl_fd.c \
		  	  ${SRCDIR}/ft_fd/ft_putnbr_fd.c \
		  	  ${SRCDIR}/ft_fd/ft_putstr_fd.c \

FT_MEM		= ${SRCDIR}/ft_mem/ft_memchr.c \
		  	  ${SRCDIR}/ft_mem/ft_memcmp.c \
		  	  ${SRCDIR}/ft_mem/ft_memcpy.c \
		  	  ${SRCDIR}/ft_mem/ft_memmove.c \
		  	  ${SRCDIR}/ft_mem/ft_memset.c \

FT_TO		= ${SRCDIR}/ft_to/ft_tolower.c \
		  	  ${SRCDIR}/ft_to/ft_toupper.c \

LIBFT 		= ${SRCDIR}/ft_atoi.c \
	  		  ${SRCDIR}/ft_bzero.c \
	 		  ${SRCDIR}/ft_calloc.c \
	  		  ${SRCDIR}/ft_itoa.c \
	  		  ${SRCDIR}/ft_split.c \

FT_PRINTF	= ${SRCDIR}/ft_printf/ft_printf.c \
		  	  ${SRCDIR}/ft_printf/ft_printf_hex.c \
		  	  ${SRCDIR}/ft_printf/ft_printf_itoa.c \
		  	  ${SRCDIR}/ft_printf/ft_printf_itoa_plus.c \
		  	  ${SRCDIR}/ft_printf/ft_printf_itoa_space.c \
		  	  ${SRCDIR}/ft_printf/ft_printf_putstr.c \
		  	  ${SRCDIR}/ft_printf/ft_printf_uitoa.c \
		  	  ${SRCDIR}/ft_printf/ft_putchar.c \

GNL			= ${SRCDIR}/get_next_line/get_next_line_bonus.c \
		  	  ${SRCDIR}/get_next_line/get_next_line.c \
		  	  ${SRCDIR}/get_next_line/get_next_line_utils_bonus.c \
		  	  ${SRCDIR}/get_next_line/get_next_line_utils.c \

SRC 		= ${FT_IS} ${FT_LST} ${FT_STR} ${FT_FD} ${FT_MEM} ${FT_TO} ${LIBFT} ${FT_PRINTF} ${GNL}

################################################################################
#                                   Objects                                    #
################################################################################

OBJ 	= ${SRC:${SRCDIR}/%.c=${OBJDIR}/%.o}
OBJDIR 	= objs

################################################################################
#                                   Colors                          	       #
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

all: ${NAME}

${NAME}: ${OBJ}
	@${AR} ${NAME} ${OBJ}
	@echo "${YELLOW}✰✰✰ Congrats! Your ${NAME} has been created ✰✰✰ :D"

${OBJDIR}/%.o: ${SRCDIR}/%.c
	@mkdir -p ${dir $@}
	@${CC} ${CFLAG} -c $< -o $@
	@echo "${GREEN}***  Compilation success  ***"

clean: 
	@rm -rf ${OBJDIR}
	@echo "${PURPLE}► Cleaning done: ${OBJDIR} directory has been removed ◄"

fclean: clean
	@rm -f ${NAME}
	@echo "${BLUE}► Fclean done: ${NAME} has been removed ◄"

re: fclean all
	@echo "${CYAN}↻↻↻ Makefile has been re'd ↺↺↺ \o/"

.PHONY: all clean fclean re bonus
