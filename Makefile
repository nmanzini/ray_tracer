# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 17:51:18 by nmanzini          #+#    #+#              #
#    Updated: 2018/04/11 10:57:35 by nmanzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRCS = 	./src/main.c 				\
		./src/call_keys_general.c	\
		./src/mlx_utils.c			\
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

# OBJ = $(SRC:.c=.o)

# LIBFT = libft/libft.a

# HEADER = ./src/rtv1.h

# W_FLAGS = -Wall -Werror -Wextra

# MLX_FLAGS = -lmlx -framework Opengl -framework Appkit

# MLX_FLAGS_MAC_AIR =  -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext $(MLX_FLAGS) 

# all: $(NAME)

# $(OBJ): %.o: %.c
# 		-@gcc -c -I libft/ $< -o $@

# $(LIBFT):
# 	-@ make -C libft 

# $(NAME): $(LIBFT) $(OBJ)
# 	-@ gcc $(MLX_FLAGS)  $(OBJ) $(LIBFT) -o $(NAME)

# clean:
# 	-@ /bin/rm -f $(OBJ)
# 	-@ make -C libft clean

# fclean: clean
# 	-@ /bin/rm -f $(NAME)
# 	-@ make -C libft fclean

# re: fclean all


INCLUDES = rtv1.h

OBJ = $(SRCS:%.c=%.o)

LFTDIR = libft/

LMLXDIR = minilibx_macos/
LIBFT = libft.a
LIBMLX = libmlx.a
FT = ft
MLX = mlx
MAKE = make
FLAGS = -Wall -Wextra -Werror 
# Add before -ggdb to find out where segfault is
SEGFAULT = -fsanitize=address 
FRAMEWORK = -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME): $(OBJ) $(LFTDIR)$(LIBFT) $(LMLXDIR)$(LIBMLX)
	-@gcc $(FLAGS) -o $(NAME) $(SEGFAULT) -ggdb $(OBJ) -I$(LFTDIR) -L$(LFTDIR) -l$(FT) \
	 -I$(LMLXDIR) -L$(LMLXDIR) -l$(MLX) \
	 $(FRAMEWORK)
	-@echo $(NAME) Ready

%.o: %.c $(INCLUDES)
	-@gcc $(FLAGS) -I$(LFTDIR) -I$(LMLXDIR) -c $(SRCS)

$(LFTDIR)$(LIBFT):
	$(MAKE) -C $(LFTDIR)$(LIBFT)

$(LMLXDIR)$(LIBMLX):
	$(MAKE) -C $(LMLXDIR) $(LIBMLX)

clean:
	-@/bin/rm -f $(OBJ)

fclean: clean
	-@/bin/rm -f $(NAME)

re: fclean all