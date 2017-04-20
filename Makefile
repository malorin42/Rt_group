NAME = rtv1

GCC = gcc

CFLAGS = -Wall -Wextra -Werror -g -O0

OBJ = obj/main.o obj/tools.o obj/matrix.o obj/object.o obj/add_pars_value.o
OBJ += obj/init_object.o obj/test_pars_tools.o obj/check_files.o
OBJ += obj/check_color_obj.o obj/check_balise_line.o obj/add_param.o obj/pars_space_value.o
OBJ += obj/test_pars_tools2.o obj/color.o obj/cone.o obj/cylinder.o obj/plane.o obj/sphere.o
OBJ += obj/path.o obj/raytracer.o obj/rotation.o

LIBFT = ./libft/libft.a

#LIBMLX = -L./minilibx/ -lmlx_Linux -L/usr/lib/x86_64-linux-gnu/ -lXext -lX11 -lm
LIBMLX = ./libmlx.a -framework OPENGL -framework Appkit

all: obj $(NAME)

$(NAME): $(OBJ)
#	@$(MAKE) -s -C ./libft/
	@$(GCC) $(CFLAGS) -o $@ $+ $(LIBFT) $(LIBMLX)
	@echo "\|/        "
	@echo "-o------.  "
	@echo "/|\     |\ "
	@echo " |      '-|"
	@echo " |        |"
	@echo " | RTv1   |"
	@echo " '--------'"

obj:
	@mkdir -p obj/

obj/%.o: src/%.c
	@$(GCC) -c $+ -o $@

clean:
	@rm -rf obj/
#	@$(MAKE) -s clean -C ./libft/

fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) -s fclean -C ./libft/

re: fclean all

.PHONY: all obj clean fclean re
