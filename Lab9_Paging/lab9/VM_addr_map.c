#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXSTR 1000

int main(int argc, char *argv[])
{
  char line[MAXSTR];
  int *page_table, *mem_map;
  unsigned int log_size, phy_size, page_size, d;
  unsigned int num_pages, num_frames;
  unsigned int offset, logical_addr, physical_addr, page_num, frame_num;

  /* Get the memory characteristics from the input file */
  fgets(line, MAXSTR, stdin);
  if((sscanf(line, "Logical address space size: %d^%d", &d, &log_size)) != 2){
    fprintf(stderr, "Unexpected line 1. Abort.\n");
    exit(-1);
  }
  fgets(line, MAXSTR, stdin);
  if((sscanf(line, "Physical address space size: %d^%d", &d, &phy_size)) != 2){
    fprintf(stderr, "Unexpected line 2. Abort.\n");
    exit(-1);
  }
  fgets(line, MAXSTR, stdin);
  if((sscanf(line, "Page size: %d^%d", &d, &page_size)) != 2){
    fprintf(stderr, "Unexpected line 3. Abort.\n");
    exit(-1);
  }

  //Compute the number of pages, and frames needed
  //number of pages = 2^(logical size - page size) ==> 2^logical addresss space / 2^page_size ==> 2^(logical_space - page_size)
  //number of frames = 2^(physical size - page size)

  /* Allocate arrays to hold the page table and memory frames map */
  page_table = //malloc(num of pages)
  mem_map = //malloc(num of frames)
  

  /* Initialize page table to indicate that no pages are currently mapped to
     physical memory */
     //for loop to indicate page_table[i] will be free
  

  /* Initialize memory map table to indicate no valid frames */
  

  /* Read each accessed address from input file. Map the logical address to
     corresponding physical address */
  fgets(line, MAXSTR, stdin);
  while(!(feof(stdin))){
    sscanf(line, "0x%x", &logical_addr);
    fprintf(stdout, "Logical address: 0x%x\n", logical_addr);
    
	/* Calculate page number and offset from the logical address */
  page_num = logical_addr >> page_size;
  offset = logical_addr & ((1<<page_size)-1);
    

    /* Form corresponding physical address */
    //get the corresponding frame
    //check for page faults
    //print the frame number 

    //physical_address
    //from the frame number we get the starting address of the frame
    //print physical_address

    /* Read next line */
    fgets(line, MAXSTR, stdin);    
  }

  return 0;
}
