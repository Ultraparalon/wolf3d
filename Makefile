# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/28 16:58:58 by iseletsk          #+#    #+#              #
#    Updated: 2018/05/12 15:23:01 by vkaidans         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_DIR :=		./sources/
OBJ_DIR :=		./objects/
INC_DIR :=		./includes/
LIB_DIR :=		./libraries/

SRC :=		main.c vs_read_file.c vs_load_textures.c vs_create_map.c\
			vs_map_valid.c vs_map_gen.c\
			vs_input.c vs_input_mouse.c vs_loop.c vs_movement.c\
			vs_render.c vs_raycast.c vs_status.c\
			vs_render_sky.c vs_render_object.c vs_render_wall.c\
			vs_render_iface.c vs_render_floor.c\
			vs_music.c vs_list.c

OBJ =		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

VOBJ =		$(addprefix $(OBJ_DIR), $(VSRC:.c=.o))

LIBFT =			$(LIBFT_DIR)libft.a
LIBFT_DIR :=	$(LIB_DIR)libft/
LIBFT_INC :=	$(LIBFT_DIR)includes/
LIBFT_FLAGS :=	-lft -L $(LIBFT_DIR)

CC_FLAGS :=		-Wall -Wextra -Werror

LINK_FLAGS :=	$(LIBFT_FLAGS)

HEADER_FLAGS :=	-I $(INC_DIR) -I $(LIBFT_INC)

CC :=		gcc

.SILENT:

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CC_FLAGS)  $(OBJ) $(LINK_FLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created wolf3d"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ) $(VOBJ)
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned wolf3d"

fclean: clean
	rm -f $(NAME) $(VIS)
	make fclean -C $(LIBFT_DIR)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned wolf3d"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
