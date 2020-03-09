SRC_DIR		:=	./src/
SRC_SRC		:=	ssl.c\
				key.c\
				provider.c\
				sslparser.c\
				cipher_parser.c\
				cipher.c\
				error.c\

SRC_OBJ		=	$(addprefix $(OBJ_DIR), $(SRC_SRC:.c=.o))
SRC			+=	$(addprefix $(SRC_DIR), $(SRC_SRC))
OBJ			+=	$(SRC_OBJ)

$(SRC_OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@