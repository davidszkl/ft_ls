NAME = libft.a
FLAGS = 

SRCDIR = src
INCDIR = inc
OBJDIR = obj
PRINTFDIR = Ft_printf

SRCS := $(shell find $(SRCDIR) -name '*.c')
OBJS := $(subst $(SRCDIR), $(OBJDIR), $(SRCS:%.c=%.o))

$(NAME): $(OBJDIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)/$(PRINTFDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	gcc -g3 $(FLAGS) -I$(INCDIR) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re