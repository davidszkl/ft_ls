NAME	= ft_ls
CC		= gcc -Wall -Wextra -Werror
SRCDIR	= src
INCDIR	= inc
LIBDIR  = inc/Libft
OBJDIR	= obj
SRC		= $(shell find src/*.c)
INC		= $(shell find inc/*.h)
OBJ		= $(subst $(SRCDIR), $(OBJDIR), $(SRC:c=o))


$(NAME): all

all: $(OBJDIR) $(OBJ)
	make -C inc/Libft
	$(CC) -o $(NAME) $(OBJ) -L$(LIBDIR) -lft -o $(NAME)

test: $(INCDIR)/*.h
	$(CC) -I$(INCDIR) -I$(LIBDIR)/inc -L$(LIBDIR) -lft $(SRC) -o $(NAME)


$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I$(INCDIR) -I$(LIBDIR)/inc -L$(LIBDIR) -lft -c $< -o $@

clean:
	make -C inc/Libft clean
	rm -f $(OBJDIR)/*

fclean: clean
	make -C inc/Libft fclean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf $(OBJDIR)

re: fclean all