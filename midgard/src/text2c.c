/* $Id: text2c.c,v 1.2 2002/02/13 11:48:12 christof Exp $ */
#include <stdio.h>

int main()
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
   return 0;
}
