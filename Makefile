# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osloboda <osloboda@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 14:11:49 by osloboda          #+#    #+#              #
#    Updated: 2019/03/04 14:18:48 by osloboda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

INCDIR = includes/
 
SRC = main.c

SRCDIR = srcs

OBJDIR = objects

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

FSRC = $(addprefix $(SRCDIR)/, $(SRC))

LIB = libft/libft.a

INCDIR = includes

FLAGS = -Wall -Werror -Wextra

.PHONY: all clean fclean re cleanlib fcleanlib relib

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) $(OBJ) $(LIB) -o $(NAME)
	@echo \\033[32m======[Compiled]========\\033[0m

$(LIB):
	make -C libft all
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h | $(OBJDIR)
	gcc $(FLAGS) -o $@ -c $< -I $(INCDIR)

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@rm -Rf $(OBJDIR)
	@echo \\033[34m======[Cleaned]=========\\033[0m

fclean: clean
	@rm -f $(NAME)

re: fclean all

cleanlib:
	make -C libft clean

fcleanlib:
	make -C libft fclean

relib:
	make -C libft re
