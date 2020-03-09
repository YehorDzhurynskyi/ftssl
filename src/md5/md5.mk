MD5_DIR		:=	$(FT_SSL_DIR)src/md5/
MD5_SRC		:=	md5.c\
				md5_funcs.c\
				md5_rounds.c\
				#md5_provider.c\

MD5_OBJ		=	$(addprefix $(FT_SSL_OBJ_DIR), $(MD5_SRC:.c=.o))
FT_SSL_SRC	+=	$(addprefix $(MD5_DIR), $(MD5_SRC:.c=.o))
FT_SSL_OBJ	+=	$(MD5_OBJ)

$(MD5_OBJ): $(FT_SSL_OBJ_DIR)%.o: $(MD5_DIR)%.c
	$(CC) $(FT_SSL_CFLAGS) $(FT_SSL_INCLUDE) $< -o $@
