NAME =	doom-nukem
CPPFLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = MacroLibX/libmlx.so -lXext -lXrender -lX11 -lm -lSDL2 -pthread
CPPFLAGS += -fPIE

MLX = MacroLibX
CUTE_PNG = cute_png
CUTE_SOUND = cute_sound

SRC = main.cpp Minilibx.cpp Image.cpp

all: lib $(NAME)

lib:
	@make -C $(MLX)
	@make -C $(CUTE_PNG)
	@make -C $(CUTE_SOUND)

$(NAME): $(SRC)
	c++ $(CPPFLAGS) -o $@ $^ -L $(MLX) $(MLX_FLAGS) cute_png/cute_png.o cute_sound/cute_sound.o

clean:

fclean:
	@rm -f $(NAME)

re:	fclean
	@make all

.PHONY: re, fclean, clean
