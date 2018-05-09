# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 17:51:18 by nmanzini          #+#    #+#              #
#    Updated: 2018/04/18 14:24:25 by nmanzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC = 	./src/main.c 				\
		./src/call_keys_general.c	\
		./src/colors_utils.c		\
		./src/data_init.c  			\
		./src/input.c				\
		./src/rotate.c				\
		./src/vect_operations.c 	\
		./src/vect_update.c 		\
		./src/vect_algebra.c 		\
		./src/obj_loops.c 			\
		./src/obj_utilities.c  		\
		./src/obj_ray_encounter.c	\
		./src/obj_read.c			\
		./src/obj_read2.c			\
		./src/call_keys_camera.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

HEADER = ./src/rtv1.h

W_FLAGS = -Wall -Werror -Wextra

MLX_FLAGS = -lmlx -framework Opengl -framework Appkit

SDL_FLAGS =  -framework SDL2 -I./SDL2.framework/Headers

MLX_FLAGS_MAC_AIR =  -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext $(MLX_FLAGS) 

all: $(NAME)

$(OBJ): %.o: %.c
		-@gcc -c -I libft/ $< -o $@

$(LIBFT):
	-@ make -C libft 

$(NAME): $(LIBFT) $(OBJ)
	-@ gcc $(W_FLAGS) $(SDL_FLAGS)  $(OBJ) $(LIBFT) -o $(NAME)

clean:
	-@ /bin/rm -f $(OBJ)
	-@ make -C libft clean

fclean: clean
	-@ /bin/rm -f $(NAME)
	-@ make -C libft fclean

re: fclean all
