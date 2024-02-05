# Define colors
YELLOW=\033[1;33m
RED=\033[1;31m
GREEN=\033[1;32m
NC=\033[0m

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
	@echo "[$(GREEN)CLIENT$(NC)]    Building $@..."
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) $(LIBS) -o $(CLNT)

$(SRV): $(LIBFT) $(OBJ_SERVER)
	@echo "[$(GREEN)SERVER$(NC)]    Building $@..."
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) $(LIBS) -o $(SRV)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h
	@mkdir -p $(@D)
	@echo "[$(GREEN)BUILD$(NC)]     Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@echo "[$(GREEN)LIBFT$(NC)]     Building library..."
	@$(MAKE) -s -C $(LIBFT_D)

clean:
	@echo "[$(RED)CLEAN$(NC)]     Cleaning object files..."
	@$(MAKE) -s -C $(LIBFT_D) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "[$(RED)FCLEAN$(NC)]    Cleaning executable files..."
	@$(MAKE) -s -C $(LIBFT_D) fclean
	@rm -rf $(CLNT)
	@rm -rf $(SRV)

re: fclean all

.PHONY: all clean fclean re
