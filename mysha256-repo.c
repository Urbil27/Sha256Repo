/* *
 * * @file my-sha256-repo.c
 * * @author G.A.
 * * @date 6/02/2024
 * * @brief First version of mysha256-repo
 * * @details  Create a tar file with only one "data file"
 * *
 * */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "s_my_sha256header.h"



extern int sha256sum_file(char *path, char outputBuffer[]) ; // HEX_SHA256_HASH_SIZE Bytes 
extern void sha256_hash_to_string (unsigned char *hash, unsigned char *outputBuffer) ;

#define OK (0)
#define ERROR_GENERATE_SHA256_HEADER (1)
#define ERROR_OPEN_DAT_FILE (2)
#define ERROR_OPEN_SHA_REPO_FILE (3)

#define ERROR_GENERATE_SHA_REPO_FILE (4)
#define ERROR_GENERATE_SHA_REPO_FILE2 (5)


#define HEADER_OK (1)
#define HEADER_ERR (2)
#define SHA256_GEN_ERR (3)


// #define DATAFILE_BLOCK_SIZE  4096


// Build RepoHeader structure with FileName (fill a new RepoHeader)
int Builsha256RepoHeader(char *FileName, struct c_sha256header *psha256header)
{
    char calc_hash[HEX_SHA256_HASH_SIZE];
    int Return_Code;

   // Fill all struct psha256header members

   bzero(psha256header, sizeof(struct c_sha256header));     // Fill all struct data with zeros

   strcpy(psha256header->fname, FileName);   // File name

   psha256header->size = 0;                  // At the moment it is an unknown value
                                             // Later we can fill it in

   // Call to function (sha256_file) to generate sha256 sum of file data
   Return_Code = sha256sum_file(FileName, calc_hash);

   if ( Return_Code != 0)  {
        fprintf(stderr,"Error on hash function call (err=%d) \n",Return_Code);
        return SHA256_GEN_ERR;
   }

   strcpy(psha256header->hash, calc_hash);     // fill  sha256 hash psha256header of argv[1]
                                               // in psha256header
   return HEADER_OK;
}



// ----------------------------------------------------------------
// (1.4) write the data file (FileName)  to RepoFile (blocks of 4096 bytes -4KB)
unsigned long WriteFileDataBlocks(int fd_DataFile, int fd_RepoFile)
{
   char FileDataBlock[READ_BLOCK_SIZE];
   unsigned long NumWriteBytes;
   int Tam, n;

   // write the data file (blocks of READ_BLOCK_SIZE  bytes) (4KB)
   NumWriteBytes =0;
   bzero(FileDataBlock, sizeof(FileDataBlock));

	///  To complete the code
	/// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	while((n = read(fd_DataFile,FileDataBlock, READ_BLOCK_SIZE))>0){
	Tam = write(fd_RepoFile,FileDataBlock,n);
	if(Tam<0){
		fprintf(stderr, "No se ha podido escribir en el archivo de repoositorio");
		return NumWriteBytes;
	}
	NumWriteBytes += Tam;
	

		
	}	
   
   
   



	/// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   
   printf("\n Total : %ld  bytes writen \n", NumWriteBytes); // Traze
   return   NumWriteBytes;
}



int main(int argc, char *argv[])
{
    insertar_fichero(argv[1],argv[2]);

}
