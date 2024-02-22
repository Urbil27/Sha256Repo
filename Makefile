CC=gcc
CFLAGS=-I.
DEPS = s_my_sha256header.h
OBJ =  sha256-ehu-lib.o mysha256-repo.o insertar_fichero.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

insertar: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -lcrypto 

clean:
	rm *.o mysha256-repo

