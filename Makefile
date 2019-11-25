nm = ft_nm

otool = ft_otool

FLAGS = gcc -g -Wall -Wextra -Werror

nm_obj = obj/nm/main.o obj/nm/ft_nm.o obj/nm/ft_lib.o\
		 obj/nm/64_bit.o obj/nm/print64.o\
		 obj/nm/32bit.o obj/nm/print32.o obj/nm/archive.o\
		 obj/nm/fat.o\
     
otool_obj = obj/otool/main.o obj/otool/ft_otool.o obj/otool/64bit.o\
			obj/otool/ft_lib.o obj/otool/32bit.o obj/otool/archive.o\
			obj/otool/fat.o\

$(nm) : $(nm_obj)
	make -C libft
	$(FLAGS) -o $(nm) $(nm_obj) libft/libft.a

$(otool) : $(otool_obj)
	make -C libft
	$(FLAGS) -o $(otool) $(otool_obj) libft/libft.a

all : $(nm) $(otool)

$(nm_obj): obj/nm/%.o: nm/%.c
	$(FLAGS) -c nm/$*.c -o $@

$(otool_obj): obj/otool/%.o: otool/%.c
	$(FLAGS) -c otool/$*.c -o $@

clean:
	make clean -C libft/
	rm -f $(nm_obj)
	rm -f $(otool_obj)

fclean: clean
	make fclean -C libft/
	rm -f $(nm)
	rm -rf $(otool)

re: fclean all