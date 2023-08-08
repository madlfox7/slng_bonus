NAME := so_long
BUILD := ./build
SRCDIR := .
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(BUILD)/%.o, $(SRCS))
INCS := -I. -Iminilibx
HEADER := $(wildcard *.h)
RM := rm -rf
CC := gcc
FLAGS := -Wall -Wextra -Werror -g3
LINKERS := -L./minilibx -lmlx -L. -lXext -lX11 -lm

all: $(BUILD) $(NAME)

$(BUILD)/%.o: $(SRCDIR)/%.c $(HEADER)
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCS) -o $(NAME) $(LINKERS)

$(BUILD):
	mkdir -p $@

clean:
	$(RM) $(BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

