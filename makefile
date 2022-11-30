# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ioduwole <ioduwole@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 15:37:48 by ioduwole          #+#    #+#              #
#    Updated: 2022/11/21 15:44:13 by ioduwole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRC =	*.c
		
CC  =  gcc 

CFLAGS = -Werror -Wall -Wextra

LIBFTDIR = libft/

LIBFTA   = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFTA)
		@$(CC) $(CFLAGS) $(SRC) $(LIBFTA) -o $(NAME)
		@echo "$(NAME) Loaded Successfully..."
$(LIBFTA): 
		@cd ./$(LIBFTDIR) && make all
clean: 
		@cd $(LIBFTDIR) && make fclean

fclean: clean
			@rm -f $(NAME)

re: fclean all