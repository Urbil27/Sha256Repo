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
	struct c_sha256header my_header;
	
	//Abrimos el fichero fuente
	if ((f_dat = open(r_dat, O_RDONLY)) == -1){
               	error("open");
        }
	//Creamos las cabeceras sha256 del fichero fuente
 	bzero(&my_header, sizeof(my_header));
    	ret = Builsha256RepoHeader(r_dat, &my_header);
		printf("Cabecera hash (ret): %d \n", ret);
    	if (ret !=HEADER_OK)
    	{
     		fprintf(stderr,"The sha256header data was not generated correctly\n");
        	return ERROR_GENERATE_SHA256_HEADER;
    	}
	//Abrimos o creamos el repo para leectura y escritura
	if ((f_repo = open(r_repo, O_RDWR|O_CREAT)) == -1){
		error("open")
	}
	printf("Archivo de repositorio abierto o creado \n");

	//Movemos el puntero al final del archivo
    if (lseek(f_repo, 0, SEEK_END) == -1){
               error("lseek");
    }
		printf("Puntero movido al final del archivo\n");

	//Escribimos el hash al final del fichero del repo
	if (write (f_repo,&my_header,sizeof(&my_header)) == -1){
		error("write");
	}
	printf("Hash escrito en el fichero de repositorio\n");
	close(f_repo);
	printf("Fichero de repositorio cerrado\n");
	close(f_dat);
	printf("Fichero fuente cerrado\n");
}
