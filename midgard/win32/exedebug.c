// compile it by gcc -o exedebug.exe exedebug.c

#include <stdio.h>

int main()
{  FILE *f=fopen("magus.exe","rb+");
   if (f)
   {  int flag=-1;
   
      fseek(f,0xdc,SEEK_SET);
      flag=fgetc(f);
      if (flag==2) printf("enabling console output\n");
      else if (flag==3) printf("disabling console output\n");
      else 
      {  printf("strange value %d\n",flag);
         fclose(f);
         return 1;
      }
      fseek(f,0xdc,SEEK_SET);
      fputc(flag^1,f);
      fclose(f);
      return 0;
   }
   else perror("magus.exe");
   return 2;
}
