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
    
  reg_key r1(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes"); // ".pdf");
  r1.get_string(".pdf", pdfclass, sizeof pdfclass, "?");
  cout << pdfclass << '\n';
  reg_key r2(HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE", "Classes", pdfclass,
  		"shell", "open");
  r2.get_string("command", pdfclass, sizeof pdfclass, "?");
  cout << pdfclass << '\n';
  
  std::string path=pdfclass;
  if (path.substr(path.size()-3)==" %1") 
     path=path.substr(0, path.size()-3);
  cout << path << '\n';
   return 0;
}
