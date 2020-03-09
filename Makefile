#	libft
LIBFT			:=	libft.a
LIBFT_DIR		:=	./libft/
LIBFT_SRC		=
LIBFT_OBJ		=
LIBFT_OBJ_DIR	:=	./obj/libft/
LIBFT_INCLUDE	:=	-I$(LIBFT_DIR)include/ -I$(LIBFT_DIR)
LIBFT_CFLAGS	:=	-c -g3 -Wall -Wextra -Werror -DDEBUG -D_DEBUG
#LIBFT_CFLAGS	:=	-c -g0 -O3 -Wall -Wextra -Werror -DNDEBUG

#	ft_ssl
FT_SSL			:=	ft_ssl
FT_SSL_DIR		:= ./
FT_SSL_SRC		=
FT_SSL_OBJ		=
FT_SSL_OBJ_DIR	:=	./obj/
FT_SSL_INCLUDE	:=	$(LIBFT_INCLUDE) -I./src/
FT_SSL_CFLAGS	:=	$(LIBFT_CFLAGS)

#	compilation
CC				:=	gcc

all: $(FT_SSL)

include ./libft/libft.mk
include ./src/src.mk
include ./src/md5/md5.mk

$(FT_SSL): $(FT_SSL_OBJ) $(LIBFT)
	$(CC) $^ -o $@

clean:
	rm -f $(LIBFT_OBJ)
	rm -f $(FT_SSL_OBJ)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(FT_SSL)

re: fclean all
