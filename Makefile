# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droly <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/04 12:24:40 by droly             #+#    #+#              #
#    Updated: 2016/05/04 14:56:00 by droly            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SOURCES = fdf.c
LIB = libft/libft.a

OBJECTS = $(SOURCES:.c=.o)

FLAGS = -Wall -Werror -Wextra -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11

MLXFLAGS = -lmlx -framework OpenGL -framework Appkit

all: makelibft $(NAME)

$(NAME): $(OBJECTS)
	@echo "\033[1;35;mStart compilation...\033[0m"
	@gcc $(LIB) $(FLAGS) $(MLXFLAGS) -o $@ $^
	@echo "\033[1;32;mCompilation success !\033[0m"

makelibft:
	@make -C libft/

%.o:%.c
	@echo "\033[1;36;mMaking .o...\033[0m"
	@gcc $(FLAGS) -c $<

clean:
	@echo "\033[1;31;mCleaning *.o (fdf)...\033[0m"
	@make clean -C libft/
	@rm -f $(OBJECTS)

fclean: clean
	@echo "\033[1;31;mDeleting all..\033[0m"
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
