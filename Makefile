CC = cc
CFLAGS = -Wall -Wextra -Werror

CLNT = client
SRV = server

SRC_DIR = src
OBJ_DIR = obj
LIBFT_D = lib/libft
FT_PRINTF_D = lib/ft_printf
INC_DIR = include

SRC_CLIENT = $(SRC_DIR)/client/client.c
SRC_SERVER = $(SRC_DIR)/server/server.c
OBJ_CLIENT = $(SRC_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER = $(SRC_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_D)/libft.a
FT_PRINTF = $(FT_PRINTF_D)/libftprintf.a
LIBS = -L$(LIBFT_D) -lft -L$(FT_PRINTF_D) -lftprintf

HEADERS = -I$(INC_DIR) -I$(LIBFT_D) -I$(FT_PRINTF_D)

all: $(CLNT) $(SRV)

$(CLNT): $(LIBFT) $(FT_PRINTF) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) $(LIBS) -o $(CLNT)

$(SRV): $(LIBFT) $(FT_PRINTF) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) $(LIBS) -o $(SRV)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_D)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_D)

clean:
	$(MAKE) -C $(LIBFT_D) clean
	$(MAKE) -C $(FT_PRINTF_D) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_D) fclean
	$(MAKE) -C $(FT_PRINTF_D) fclean
	rm -f $(CLNT)
	rm -f $(SRV)

re: fclean all

.PHONY: all clean fclean re