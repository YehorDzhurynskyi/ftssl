SRC_DIR		:=	$(FT_SSL_DIR)src/
SRC_SRC		:=	main.c\
				error.c\
				request.c\
				provider.c\
				buffer.c\

SRC_OBJ		=	$(addprefix $(FT_SSL_OBJ_DIR), $(SRC_SRC:.c=.o))
FT_SSL_SRC	+=	$(addprefix $(SRC_DIR), $(SRC_SRC:.c=.o))
FT_SSL_OBJ	+=	$(SRC_OBJ)

$(SRC_OBJ): $(FT_SSL_OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FT_SSL_CFLAGS) $(FT_SSL_INCLUDE) $< -o $@
