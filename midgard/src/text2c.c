/* $Id: text2c.c,v 1.3 2003/09/01 06:47:58 christof Exp $ */
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
