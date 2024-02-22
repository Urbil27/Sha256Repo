#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "s_my_sha256header.h"
#define error(a) {perror(a); exit(1);};
#define BUFSIZE 80

//Funcion insertar archivo
insertar_fichero (char *r_dat, char *r_repo)
{
	int stderr = 2;
	int f_dat,f_repo;
	int n, ret;
	char buf[BUFSIZE];
	struct c_sha256header my_sha256header;
	//Abrimos o creamos el repo para leectura y escritura
	if ((f_repo = open(r_repo, O_RDWR|O_CREAT)) == -1){
		error("open")
	}
	//Abrimos el fichero fuente
	if ((f_dat = open(r_dat, O_RDONLY)) == -1){
               	error("open");
        }
	//Creamos las cabeceras sha256 del fichero fuente
 	bzero(&my_sha256header, sizeof(my_sha256header));
    	ret = Builsha256RepoHeader(r_dat, &my_sha256header);
		printf("Cabecera hash (ret): %d \n");
    	if (ret !=HEADER_OK)
    	{
     		fprintf(stderr,"The sha256header data was not generated correctly\n");
        	return ERROR_GENERATE_SHA256_HEADER;
    	}

	//Movemos el puntero al final del archivo
        if (lseek(f_repo, 0, SEEK_END) == -1){
                error("lseek");
        }
	//Escribimos el hash al final del fichero del repo
	if (write (f_repo,ret,atoi(ret)) == -1){
		error("write");
	}
	close(f_repo);
	close(f_dat);
}
