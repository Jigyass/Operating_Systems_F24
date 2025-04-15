/*
 * Example of using mmap. Taken from Advanced Programming in the Unix
 * Environment by Richard Stevens.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <unistd.h>
#include <string.h>  /* memcpy */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void err_quit (const char * mesg)
{
  printf ("%s\n", mesg);
  exit(1);
}

void err_sys (const char * mesg)
{
  perror(mesg);
  exit(errno);
}

int main (int argc, char *argv[])
{
  int fdin, fdout, i;
  char *src, *dst, buf[256];
  struct stat statbuf;

  src = dst = NULL;

  if (argc != 3)
    err_quit ("usage: memmap <fromfile> <tofile>");

  /* 
   * open the input file 
   */
  if ((fdin = open (argv[1], O_RDONLY)) < 0) {
    sprintf(buf, "can't open %s for reading", argv[1]);
    perror(buf);
    exit(errno);
  }

  /* 
   * open/create the output file 
   */
  if ((fdout = open (argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0) {
    sprintf (buf, "can't create %s for writing", argv[2]);
    perror(buf);
    exit(errno);
  }

  /* 
   * 1. find size of input file 
   */
  if(fstat(fdin, &statbuf) != 0) err_sys("fstat failed\n");
  long filesize = statbuf.st_size;
  
  /* 
   * 2. go to the location corresponding to the last byte 
   */
  if(lseek(fdout, filesize - 1, SEEK_SET) == -1) err_sys("lseek failed\n");

  /* 
   * 3. write a dummy byte at the last location 
   */
  // this tells the OS that at least this many bytes shall be "reserved" for this file
  char dummy = 'a';
  if(write(fdout, &dummy, 1) == -1) err_sys("write failed\n");

  /* 
   * 4. seek back to offset 0 in the output file
   */
  lseek(fdout, 0, SEEK_SET);

  /* 
   * 5. mmap the input file 
   */
  src = (char *) mmap(NULL, filesize, PROT_READ, MAP_SHARED, fdin, 0);
  if((long) src == -1) err_sys("mmap input file failed");
  /* 
   * 6. mmap the output file 
   */
  dst = (char *) mmap(NULL, filesize, PROT_WRITE, MAP_SHARED, fdout, 0);
  if((long) dst == -1) err_sys("mmap output file failed");

  /* 
   * 7. copy the input file contents to the output file 
   */
  /* Memory can be dereferenced using the * operator in C.  This line
    * stores what is in the memory location pointed to by src into
    * the memory location pointed to by dst.
    * 
    * Hint: This operation is not what we're looking for since this only copies a single character (1 byte).
    * Consider using the `memcpy` function to copy a specified number of bytes.
    */
  memcpy(dst, src, filesize);
}


