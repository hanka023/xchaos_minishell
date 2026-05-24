# Název výsledného programu
NAME = lex

# Překladač a příznaky
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I gnl -I utils -I fPie

# Seznam všech .c souborů
SRC = main.c \
      gnl/get_next_line.c \
      gnl/get_next_line_utils.c 
	

# Změna koncovek .c na .o pro objekty
OBJ = $(SRC:.c=.o)

# Hlavní pravidlo
all: $(NAME)

# Jak vytvořit výsledný program z objektů
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Pravidlo pro promazání objektových souborů
clean:
	rm -f $(OBJ)

# Pravidlo pro kompletní smazání (včetně programu)
fclean: clean
	rm -f $(NAME)

# Pravidlo pro "přestavbu" od nuly
re: fclean all

.PHONY: all clean fclean re