# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 17:07:51 by droly             #+#    #+#              #
#    Updated: 2016/05/02 19:07:59 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = fdf.c

OBJ = $(SRC:.c=.o)

LIB = libft/libft.a

FLAGS = -Wall -Wextra -Werror

.PHONY: clean fclean re makelibft

all: $(NAME)

$(NAME) : $(OBJ) makelibft
	@clang $(FLAGS) $(SRC) $(LIB) -lmlx -framework OpenGL -framework Appkit -o $(NAME)
	@echo "Compilation completed."

makelibft:
	@make -C libft/

clean:
	@rm -f $(OBJ)
	@make clean -C libft/
	@echo "\033[0;31mSupression .o (fdf)...\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft/
	@echo "\033[0;31mSupression totale (fdf)...\033[0m"

re: fclean all
