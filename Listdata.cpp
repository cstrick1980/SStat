//------------------------------------------------------------------+
// PROGRAM - listdata.cpp
//           Lists out the current data set.                         
//                                                                   
// 29 Apr 91 - Modified the routine to use data,row,col as global    
//             variables.
//  1 Feb 92 - Changed <os9stat.h> to "os9stat.h"                    
//  2 Feb 92 - Changed using data[] to working.osd
// 13 Aug 92 - Added the ability to pause the output and quit.       
// 6 Sep 92 - Added a check to make sure trying to list without a
//             selected datafile returns a error.                   
// 20 Dec 92 - Modified the number of cols, printed at one time.    
//             Also modified the number of lines printer under GUI  
//            mode.
// 28 Dec 92 - Made the number of rows list when in tty mode 20.     
// 19 Feb 93 - Added the PRINTER variable to turn off/on printer.
// 24 Feb 93 - Modified the rows printed to the screen.
//  1 Jun 93 - Added the lastrow to insure blank row won't be printed
//             as last row.                                          
// 13 Jun 93 - Changed the <=prtcol to <prtcol to stop the printing
//             of the last col twice, when maxcol was reached.       
// 15 Jun 93 - Changed above line back and did check on
//             maxcol+prtcol-1 instead of maxcol+prtcol.
// 19 Jun 93 - Added comments to explain process in attempt to get
//             output printing correctly. Changed l -> linecnt
//             Added static char prompt, for prompt string.
//             Changed PRINTER==FALSE -> PRINTER!=TRUE to solve
//             apparent stack overwrite. Did the same for GUI. Added
//             fflush(0) to clear print buffer.
//             Also changed lastprt -> firstcol and prtcol -> lastcol
//====================================================================
// 15 Feb 95 - Started porting this over to Turbo Visual C++
// 11 Jun 97 - Started port to C++ Builder and converted to C++
// 24 Jun 97 - Added the ability to print to the memo field on the
//             main screen.
//--------------------------------------------------------------------+

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <iostream.h>
#include <vcl\vcl.h>
#include "TSSData.h"
#include "mathss.h"
#include "TSStat.h"

int ListData()
{
   int j;
   register int i;

   char buff[255];
   char value[20];

   /**********************************************************/
   /* If the max col + the last col is < col then we want to */
   /* readd max col back again; otherwise, this is the last  */
   /* time through and we need to use col as the last col    */
   /**********************************************************/

   /* print out var titles from last title printed */

   sprintf(buff,"   \0");

   for(j=0; j<=SSData->col; j++) {
      sprintf(value,"   var%2d\0",j+1);
      strcat(buff,value);
   }

   SStat->Results->Lines->Add(buff);

   sprintf(buff,"\n\n\0");
   for(i=0; i<=SSData->row; i++) { /* [2] Print out all rows in data set */
      sprintf(buff,"\0");
      sprintf(value,"%3d \0",i+1);
      strcat(buff,value);
      for (j=0; j<=SSData->col; j++) {
         sprintf(value,"%7.4g \0",SSData->GetData(i,j));
         strcat(buff,value);
      }

      SStat->Results->Lines->Add(buff);
   }
   return 0;
}

