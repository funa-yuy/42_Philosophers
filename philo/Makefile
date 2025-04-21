# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miyuu <miyuu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 01:21:55 by miyuu             #+#    #+#              #
#    Updated: 2025/04/21 21:35:59 by miyuu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = bin
HEADER_DIR = include

# Source files
SRC_FILES = main.c \
			init_univ_rules.c \
			printf_philo_status.c \
			init_thread_arg.c \
			mulch_thread.c \
			init_die_judge.c \
			get_now_time_ms.c \
			setup_thread_resources.c \
			judgement_stop_thread.c \
			ft_atoi.c \
			ft_isdigit.c \
			utils.c \
			take_put_forks.c

# Header files
HEADER = $(HEADER_DIR)/philo.h


SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Build the program
all: $(OBJ_DIR) $(NAME)

# Create OBJ_DIR
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create the final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile each .c file into a .o file inside OBJ_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

# Clean all object files
clean:
	rm -rf $(OBJ_DIR)

# Clean all binary
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re
