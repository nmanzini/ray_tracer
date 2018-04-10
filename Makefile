# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 17:51:18 by nmanzini          #+#    #+#              #
#    Updated: 2018/04/10 18:43:43 by nmanzini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRCS = 	./src/main.c 				\
		./src/call_keys_general.c	\
		./src/mlx_utils.c			\
		./src/colors_utils.c		\
		./src/data_init.c  			\
		./src/input.c				\

# MLX_FLAGS = -lmlx -framework Opengl -framework Appkit

# MLX_FLAGS_MAC_AIR =  -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext $(MLX_FLAGS) 

INCLUDES = rtv1.h keys.h mlx_constants.h

OBJ = $(SRCS:%.c=%.o)

LFTDIR = libft/

LMLXDIR = minilibx_macos/
LIBFT = libft.a
LIBMLX = libmlx.a
FT = ft
MLX = mlx
MAKE = makemake
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
	$(MAKE) -C $(LFTDIR) $(LIBFT)

$(LMLXDIR)$(LIBMLX):
	$(MAKE) -C $(LMLXDIR) $(LIBMLX)

clean:
	-@/bin/rm -f $(OBJ)

fclean: clean
	-@/bin/rm -f $(NAME)

re: fclean all
