# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 12:13:04 by otodd             #+#    #+#              #
#    Updated: 2024/04/23 13:43:30 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW		=	\033[1;33m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
NC			=	\033[0m

CC			=	cc
CFLAGS 		= 	-Wall -Wextra -Werror

CLNT 		= 	client
SRV			= 	server

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj
LIBFT_D 	= 	libft
INC_DIR 	= 	include

SRC_CLIENT	=	$(SRC_DIR)/client/client.c
SRC_SERVER 	= 	$(SRC_DIR)/server/server.c
OBJ_CLIENT 	= 	$(SRC_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER 	= 	$(SRC_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT 		= 	$(LIBFT_D)/build/libft.a
LIBS 		= 	-L$(LIBFT_D)/build -lft

HEADERS 	= 	-I$(INC_DIR) -I$(LIBFT_D)

all: $(CLNT) $(SRV)

$(CLNT): $(LIBFT) $(OBJ_CLIENT)
	@echo "[$(GREEN)MINITALK$(NC)]  Building $@..."
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) $(LIBS) -o $(CLNT)

$(SRV): $(LIBFT) $(OBJ_SERVER)
	@echo "[$(GREEN)MINITALK$(NC)]  Building $@..."
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) $(LIBS) -o $(SRV)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h
	@mkdir -p $(@D)
	@echo "[$(BLUE)MINITALK$(NC)]  Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	@echo "[$(CYAN)MINITALK$(NC)]  Building library..."
	@$(MAKE) -s -C $(LIBFT_D)

clean:
	@echo "[$(YELLOW)MINITALK$(NC)]  Cleaning object directory..."
	@$(MAKE) -s -C $(LIBFT_D) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "[$(RED)MINITALK$(NC)]  Cleaning executable directory..."
	@$(MAKE) -s -C $(LIBFT_D) fclean
	@rm -rf $(CLNT)
	@rm -rf $(SRV)

re: fclean all

.PHONY: all clean fclean re
