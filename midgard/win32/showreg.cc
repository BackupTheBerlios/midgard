#include <windows.h>
//#include <io.h>
#include "registry.h"
#include <iostream>
//#include <process.h>
//#include <stdlib.h>
#include <string>

int main()
{  
  char pdfclass[1024];
    
  reg_key r1(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes",".pdf",0);
  r1.get_string(0, pdfclass, sizeof pdfclass, "");
  cout << pdfclass << '\n';
  if (*pdfclass)
  {  reg_key r2(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes", pdfclass,
  		"shell", "open", "command", 0);
     r2.get_string(0, pdfclass, sizeof pdfclass, "");
     cout << pdfclass << '\n';
  
     std::string path=pdfclass;
     if (path.size()>3 && path.substr(path.size()-3)==" %1") 
        path=path.substr(0, path.size()-3);
     else if (path.size()>5 && path.substr(path.size()-5)==" \"%1\"") 
        path=path.substr(0, path.size()-5);
     cout << path << '\n';
   }
   return 0;
}
