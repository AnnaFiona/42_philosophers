NAME		= philo

DEF_COLOR = \033[0;39m
GREEN = \033[0;92m

MY_SOURCES 	=	atoi_with_int_check.c \
				forks.c \
				input_check.c \
				main.c \
				make_philos.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CFLAGS = -Wall -Werror -Wextra

CC = @cc

.PHONY: clean fclean all

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@cc $(CFLAGS) $(MY_OBJECTS) -pthread -o $(NAME)
	@echo "$(GREEN)compilation done$(DEF_COLOR)"

clean:
	@rm -f $(MY_OBJECTS)
	@echo all .o-files deleted

fclean: clean
	@rm -f philo
	@echo
	@echo ...and the philo too

re: fclean all

debug: CFLAGS += -g
debug: re

val: all
	make -C ./ clean
	valgrind --leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		--log-file=valgrind-out.txt \
		./$(NAME) 4 1 1 1
	code valgrind-out.txt