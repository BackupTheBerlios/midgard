#include <windows.h>
//#include <winreg.h>
#include <io.h>
#include "registry.h"
#include <process.h>
#include <stdlib.h>

#define CYGWIN_INFO_CYGNUS_REGISTRY_NAME "Cygnus Solutions"
#define CYGWIN_INFO_CYGWIN_REGISTRY_NAME "Cygwin"
#define CYGWIN_INFO_PROGRAM_OPTIONS_NAME "Program Options"
#define CYGWIN_INFO_CYGWIN_MOUNT_REGISTRY_NAME "mounts v2"
#define CYGWIN_INFO_CYGDRIVE_FLAGS "cygdrive flags"
#define CYGWIN_INFO_CYGDRIVE_PREFIX "cygdrive prefix"
#define CYGWIN_INFO_CYGDRIVE_DEFAULT_PREFIX "/cygdrive"

int main()
{  char buf[MAX_PATH];
   char posix_path[MAX_PATH];
   DWORD posix_path_size=MAX_PATH;
   const char cygpath[]="\\cygwin";

// from path.cc
   reg_key r1 (HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE",
               CYGWIN_INFO_CYGNUS_REGISTRY_NAME,
               CYGWIN_INFO_CYGWIN_REGISTRY_NAME,
               CYGWIN_INFO_CYGWIN_MOUNT_REGISTRY_NAME,
               NULL);
   HKEY key = r1.get_key ();
   
   int res = RegEnumKeyEx (key, 0, posix_path, &posix_path_size, NULL,
			  NULL, NULL, NULL);
   if (res == ERROR_SUCCESS)
   else
   {  reg_key subkey = reg_key (key, KEY_READ, "/", NULL);
      char native_path[MAX_PATH];
      subkey.get_string ("native", native_path, sizeof (native_path), "");
      subkey.get_int("flags");
   }
}
