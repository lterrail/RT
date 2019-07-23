# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/27 18:24:40 by fcottet           #+#    #+#              #
#    Updated: 2019/06/21 10:04:33 by temehenn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt
CC = gcc
LIBFTDIR = ./libft
SRCDIR = src
OBJDIR = obj
FLAGS= -Wall -Wextra -Werror -O3
SRCFILE = core/main.c\
		  core/core.c\
		  core/closest_obj.c\
		  core/init_var.c\
		  core/print_bar.c\
		  core/load_obj.c\
		  core/raytracer.c\
		  core/texture.c\
		  core/texture2.c\
		  core/perlin.c\
		  core/shaders.c\
		  core/perlin_interpolation.c\
		  core/loading_bar.c\
		  light/diffuse_color.c\
		  light/get_color.c\
		  light/reflection.c\
		  light/refraction.c\
		  light/direct_light.c\
		  math_tool/basic_matrix.c\
		  math_tool/init_polynom.c\
		  math_tool/trans_matrix.c\
		  math_tool/trans_matrix2.c\
		  math_tool/quadric.c\
		  math_tool/inter_quadric.c\
		  math_tool/op_vector.c\
		  math_tool/cal_point.c\
		  math_tool/dbl_swap.c\
		  math_tool/resolve.c\
		  math_tool/resolv4.c\
		  math_tool/inter_mesh.c\
		  math_tool/inter_tore.c\
		  math_tool/inter_cube.c\
		  math_tool/clamp.c\
		  math_tool/closest_inter.c\
		  math_tool/op_vector2.c\
		  mlx_func/event.c\
		  mlx_func/light_pixel.c\
		  parser/read_file.c\
		  parser/parse.c\
		  parser/check_scene.c\
		  parser/check_value_obj.c\
		  parser/check_obj.c\
		  parser/check_light.c\
		  parser/check_mesh.c\
		  parser/check_var.c\
		  parser/check_cam.c\
		  parser/check_param.c\
		  parser/fill_obj.c\
		  parser/fill_light.c\
		  parser/fill_param.c\
		  parser/fill_obj_material.c\
		  parser/fill_mesh_value.c\
		  parser/get_type.c\
		  parser/free_func.c\
		  parser/list_err.c\
		  parser/error.c\
		  parser/quit_all.c\
		  parser/util_is_function.c\
		  parser/util_count_function.c\
		  parser/util_get_function.c\

SRC = $(addprefix $(SRCDIR), $(SRCFILE))

OBJFILE = $(SRCFILE:.c=.o)

OBJ = $(addprefix $(OBJDIR)/,$(OBJFILE))

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) -g $(FLAGS) -o $@ -c $< -I include/ -I $(LIBFTDIR)
	@echo "File compiled : " $<

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) -g -o $(NAME) $(OBJ) -I libft/ ./libft/libft.a -lmlx -framework AppKit -framework OpenGL #-lXext -lX11 -lm -lpthread#
	@echo "\033[32mCompilation SUCCEED. Binary created :\033[32;1m" $@

$(OBJ): | $(OBJDIR)

$(OBJDIR):
	@mkdir $@
	@make -C libft/
	@mkdir -p obj/core/
	@mkdir -p obj/math_tool/
	@mkdir -p obj/light/
	@mkdir -p obj/mlx_func/
	@mkdir -p obj/parser/

clean:
	@make -C libft/ clean
	@rm -rf $(OBJDIR)
	@echo "\033[36mObjects have been deleted.\033[00m"

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)
	@echo "\033[36m"$(NAME) "have been deleted.\033[00m"

re: fclean all

.PHONY: all clean fclean re
