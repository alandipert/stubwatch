OBJ = stubwatch.o
SO = stubwatch.so

%.o: %.c
	gcc -c -fPIC -o $@ $< -I.

$(SO): $(OBJ)
	gcc $< -shared -o $(SO)

all: $(SO)

clean:
	rm -f *.o *.so


