#include <windows.h>
//#include <winreg.h>
#include <io.h>
#include "registry.h"
#include <process.h>

#define CYGWIN_INFO_CYGNUS_REGISTRY_NAME "Cygnus Solutions"
#define CYGWIN_INFO_CYGWIN_REGISTRY_NAME "Cygwin"
#define CYGWIN_INFO_PROGRAM_OPTIONS_NAME "Program Options"
#define CYGWIN_INFO_CYGWIN_MOUNT_REGISTRY_NAME "mounts v2"
#define CYGWIN_INFO_CYGDRIVE_FLAGS "cygdrive flags"
#define CYGWIN_INFO_CYGDRIVE_PREFIX "cygdrive prefix"
#define CYGWIN_INFO_CYGDRIVE_DEFAULT_PREFIX "/cygdrive"

int main()
{  char buf[10240];
   const char cygpath[]="\\cygwin";
   getcwd(buf,sizeof(buf)-sizeof cygpath);
   printf("WD: '%s'\n",buf);
   if (access(buf,F_OK)) { printf("access('.',F_OK) failed\n"); return 2; }
   strcat(buf,cygpath);
   if (access(buf,F_OK)) { printf("access('cygwin',F_OK) failed\n"); return 3; }

// from path.cc
   reg_key r1 (HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE",
               CYGWIN_INFO_CYGNUS_REGISTRY_NAME,
               CYGWIN_INFO_CYGWIN_REGISTRY_NAME,
               CYGWIN_INFO_CYGWIN_MOUNT_REGISTRY_NAME,
               NULL);
//   reg_key subkey = reg_key (key, KEY_READ, posix_path, NULL);
                                                           
      /* chdir("cygwin\\bin"); */
      int ipc_pid=_spawnl(_P_NOWAIT,"cygwin\\bin\\ipc-daemon","ipc-daemon",NULL);
      int pgsql_pid=_spawnl(_P_NOWAIT,"cygwin\\bin\\postmaster","postmaster","-?I",NULL);
      _spawnl(_P_WAIT,"midgard","midgard",NULL);
}
