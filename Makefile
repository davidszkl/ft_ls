LS = ft_ls
all:
	cmake -S . -B build
	make -C build
clean:
	rm -rf build
fclean:
	rm -f $(LS)
re: clean fclean all

.PHONY:
	all clean fclean re