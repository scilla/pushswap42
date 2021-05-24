NAME_PUSH	= push_swap
NAME_CHECKER = checker

CC 		= gcc
CFLAGS	= -Wall -Wextra -Werror

PUSH_SRCS =	parser.c				\
			utils.c				\
			main.c				\
			moves_printer.c		\
			../checker_files/checker_utils.c	\
			../checker_files/checker_main.c		\

PUSH_DIR = 	./push_swap_files

CHECKER_SRCS =	checker_main.c				\
				get_commands.c		\
				checker.c			\
				commands.c			\
				checker_utils.c			


CHECKER_DIR = ./checker_files

LIBFT_DIR = 	./libft

PUSH_DIRSRCS = $(addprefix ${PUSH_DIR}/, ${PUSH_SRCS})

PUSH_OBJS	= ${PUSH_DIRSRCS:.c=.o}

CHECKER_DIRSRCS = $(addprefix ${CHECKER_DIR}/, ${CHECKER_SRCS})

CHECKER_OBJS	= ${CHECKER_DIRSRCS:.c=.o}

%.o: %.c
			$(CC) ${CFLAGS} -g -c $< -o $@ 

all: 		checker push_swap
			@(echo "\033[32m===  PUSH_SWAP AND CHECKER PROJECT COMPILED  ===\033[0m")

push_swap: libft ${PUSH_OBJS}
			$(CC) ${CFLAGS} -o ${NAME_PUSH} ${PUSH_OBJS} libft.a
			@(echo "\033[32m===  PUSH_SWAP PROJECT COMPILED  ===\033[0m")

checker: libft ${CHECKER_OBJS}
			$(CC) ${CFLAGS} ${CHECKER_OBJS} libft.a -o ${NAME_CHECKER}
			@(echo "\033[32m===  CHECKER PROJECT COMPILED  ===\033[0m")

libft:
			make bonus -C $(LIBFT_DIR)
			cp libft/libft.a ./libft.a


clean:
			make clean -C $(LIBFT_DIR)
			rm -f ./checker_files/*.o
			rm -f ./push_swap_files/*.o

fclean: clean
			rm -f $(NAME_PUSH) $(NAME_CHECKER) ./libft.a
			make fclean -C $(LIBFT_DIR)
			@echo "\033[33m=== PROJECT CLEANED ===\033[0m"

re: fclean all

banana: ${CHECKER_DIRSRCS} ${CHECKER_OBJS}

.PHONY: all clean fclean re push_swap checker libft