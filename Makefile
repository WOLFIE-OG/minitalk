CC = cc
CFLAGS = -Wall -Wextra -Werror

CLNT = client
SRV = server

SRC_DIR = src
OBJ_DIR = obj
LIBFT_D = libft
INC_DIR = include

SRC_CLIENT = $(SRC_DIR)/client/client.c
SRC_SERVER = $(SRC_DIR)/server/server.c
OBJ_CLIENT = $(SRC_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER = $(SRC_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_D)/build/libft.a
LIBS = -L$(LIBFT_D)/build -lft

HEADERS = -I$(INC_DIR) -I$(LIBFT_D)

all: $(CLNT) $(SRV)

$(CLNT): $(LIBFT) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) $(LIBS) -o $(CLNT)

$(SRV): $(LIBFT) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) $(LIBS) -o $(SRV)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_D)

clean:
	$(MAKE) -C $(LIBFT_D) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_D) fclean
	rm -rf $(CLNT)
	rm -rf $(SRV)

re: fclean all

.PHONY: all clean fclean re