LS = ft_ls
all:
	cmake -S . -B build
	make -C build
	export LANG=C.UTF-8
	export LC_ALL=C.UTF-8
clean:
	rm -rf build
fclean:
	rm -f $(LS)
re: clean fclean all

.PHONY:
	all clean fclean re