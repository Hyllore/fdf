# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 17:07:51 by droly             #+#    #+#              #
#    Updated: 2016/05/03 16:49:16 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf.c

OBJ = $(SRC:.c=.o)

LIB = libft/libft.a

FLAGS = -Wall -Wextra -Werror

FLAGS_MLX = -lmlx -framework OpenGL -framework Appkit

.PHONY: clean fclean re makelibft

all: $(NAME)

$(NAME) : $(OBJ) makelibft
	clang $(FLAGS) $(SRC) $(LIB) $(FLAGS_MLX) -o $(NAME)
	@echo "\033[1;36mCompilation completed.\033[0m"

makelibft:
	@make -C libft/

clean:
	@rm -f $(OBJ)
	@make clean -C libft/
	@echo "\033[1;31mSupression .o (fdf)...\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "\033[1;31mSupression totale (fdf)...\033[0m"

re: fclean all
