//--------------------------------------------------------------------+
// PROGRAM: ReadData                                                  |
// This routine allows you to read an ASCII data file into an array   |
// CALLED BY: start_stat                                              |
//                                                                    |
// 29 Apr 91 - Modified the routine to handle data,row,col as global  |
//             variables.                                             |
// 28 Jun 91 - Modified the routine to handle multiple spaces in the  |
//             data file.                                             |
// 24 Nov 91 - Changed the save prompt to read.                       |
//  5 Jan 92 - Changed <os9stat.h> to "os9stat.h"                     |
//             Changed the gets to scanf for getting the filename due |
//             to the OS9STAT> prompt being returned.                 |
//  2 Feb 92 - Added the ability to read binary data.                 |
//             Changed using data[] to use a work file.               |
// 22 Feb 92 - Changed the method from reading the data from getc to  |
//             fscanf.                                                |
// 28 Jun 92 - Added modulo so that a line count would be printed     |
//             every 10 lines to let the user know it's working.      |
// 10 Aug 92 - Use fprint to print file not found error message.      |
//             Also used it for printing record count.                |
// 30 Aug 92 - Modified *filename to filename[80 and changed the      |
//             scanf's to scanf(...,&var[0])                          |
// 18 Oct 92 - Added code to correctly print out number of recs read. |
// 13 Jan 93 - Added the void typdef to readdata                      |
// 22 Feb 93 - Removed the MEMORY compiler defs.                      |
// 16 Mar 93 - Changed DEBUGS from printf to fprintf                  |
//  7 Apr 93 - Added FILEOPEN check to close opened files.            |
//  1 Jun 93 - Added better error messages.                           |
//  8 Jun 93 - Added the modulo() to the binary option so the user can|
//             see the data being read.                               |
//---------------------------------------------------------------------
// 20 Feb 95 - Started the port to the windows version, which involved
//             converting this routine to ANSI-C, also renamed to
//             ReadFile from ReadData
//  8 Mar 95 - Made the data, row and col values global, need to figure
//             out how to encapsulate this process.
//-------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define NULLCHARPTR (char *) 0

extern float data[];
extern int row,col;

int Error(const char *message);

int ReadData(char *filename)
{
  FILE *fp;
  char buffer[256];
  char *str;
  char *tokptr;
  char *delimit=" \t";
  float dval;
  int chk;
  int CountEm=0;
  int j;

  row=0;
  col=0;

  fp = fopen(filename, "r");
  if (!fp) {
    Error("Opening file");
    return -1;
  }
  while (fgets(buffer, 255, fp) != NULL) {
     j=0;

     str=buffer;
     while ( (tokptr = strtok (str, delimit)) != NULLCHARPTR ) {
        chk=sscanf(tokptr,"%f",&dval);
        if (chk == 1) {

           *(data+j+row*col)=dval; /* Note, since row=0 for 1st row, val of col doesn't matter */

	  if (CountEm == 0) col++;
          j++;
       }

       if (chk == 0) {
	  fprintf(stderr,"Bad input for data[%d,%d]|",row,col);
	  if (CountEm == 0) col++;
          j++;
       }
       str = NULLCHARPTR;
    }

    row++;
    CountEm=1;
  }
  fclose(fp);
// Need to decrement since C arrays start at 0
  row--;
  col--;
  return 0;
}

int Error(const char *message)
{
   fprintf(stderr,"\n\nError: %s\n\n", message);
   fprintf(stderr,"ReadFile: Path Name Not Found\007\n");
   fprintf(stderr,"Either filename was mispelled, doesn't exist\n");
   fprintf(stderr,"or is not in current directory.\n");
   return -1;
}

