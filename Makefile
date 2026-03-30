NAME = ft_malcolm

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -Isrc
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_DIR = obj

# Sadece dosya isimlerini belirtiyoruz (dizin yolu olmadan)
SRC_FILES = main.c network.c args_parser.c parsing.c

# Obje dosyaları
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Make'in .c dosyalarını hem ana dizinde (.) hem de src/ dizininde aramasını sağlar
vpath %.c . src

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

.PHONY: all clean fclean re $(OBJ_DIR)

# Rule to create the object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
