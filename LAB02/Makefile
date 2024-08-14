CC = gcc
CFLAGS = -Wall -c
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
%.o: %.c $(DEPS)	# all objects files depend on their respective .c file along with all of the DEPS
	$(CC) $(CFLAGS) $< -o $@

all: $(NAME)
$(NAME): $(OBJECTS)
	@ar -r $(NAME) $(OBJECTS)

# -r: recursive, removal of directories and their contents
# -f: force, ignores non-existent files and doesn't prompt for confirmation
# clean: remove .o files
clean:
	rm -f *.o

# fclean: remove .o files and binary
fclean: clean
	rm -f $(NAME)
# re: do fclean and re-make your binary
re: fclean all