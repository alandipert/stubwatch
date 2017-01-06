%.o: %.c
	gcc -c -fPIC -o $@ $< -I.

all: stubwatch.o
	gcc $< -shared -o stubwatch.so

clean:
	rm -f *.o *.so


