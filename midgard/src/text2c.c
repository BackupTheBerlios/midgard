/* $Id: text2c.c,v 1.1 2002/02/13 11:20:22 christof Exp $ */
#include <stdio.h>

void main()
{  int c;
   fputs("\t\"",stdout);
   while ((c=fgetc(stdin))!=-1)
   {  switch(c)
      {  case '\\': putchar(c); putchar(c);
            break;
         case '\n': fputs("\\n\"\n\t\"",stdout);
            break;
         case '"': putchar('\\'); putchar(c);
            break;
         default: putchar(c);
            break;
      }
   }
   fputs("\"\n",stdout);
}
