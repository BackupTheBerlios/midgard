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

#if 0
int main()
{  char buf[MAX_PATH];
   char posix_path[MAX_PATH];
   DWORD posix_path_size=MAX_PATH;
   const char cygpath[]="\\cygwin";
   getcwd(buf,sizeof(buf)-sizeof cygpath);
   printf("WD: '%s'\n",buf);
   if (access(buf,F_OK)) { perror("access('.',F_OK)"); return 2; }
   strcat(buf,cygpath);
   if (access(buf,F_OK)) { perror("access('cygwin',F_OK)"); return 3; }

// from path.cc
   reg_key r1 (HKEY_LOCAL_MACHINE, KEY_READ, "SOFTWARE",
               CYGWIN_INFO_CYGNUS_REGISTRY_NAME,
               CYGWIN_INFO_CYGWIN_REGISTRY_NAME,
               CYGWIN_INFO_CYGWIN_MOUNT_REGISTRY_NAME,
               NULL);
   HKEY key = r1.get_key ();
   
   int res = RegEnumKeyEx (key, 0, posix_path, &posix_path_size, NULL,
			  NULL, NULL, NULL);
   if (res != ERROR_SUCCESS)
   {
   {  // create the keys
   
      reg_key subkey = reg_key (key,
                                KEY_ALL_ACCESS,
                                "/", NULL);
      subkey.set_string ("native", buf);
      subkey.set_int ("flags", 0xa);
   }   
      int len=strlen(buf);
      strncpy(buf+len,"\\bin",sizeof(buf)-len);
   {
      reg_key subkey = reg_key (key,
                                KEY_ALL_ACCESS,
                                "/usr/bin", NULL);
      printf("bin:native=%d\n",buf);
      subkey.set_string ("native", buf);
      subkey.set_int ("flags", 0xa);
   }

      strncpy(buf+len,"\\lib",sizeof(buf)-len);
   {
      reg_key subkey = reg_key (key,
                                KEY_ALL_ACCESS,
                                "/usr/lib", NULL);
      subkey.set_string ("native", buf);
      subkey.set_int ("flags", 0xa);
   }
      buf[len]=0;
   }
   else
   {  reg_key subkey = reg_key (key, KEY_READ, "/", NULL);
      char native_path[MAX_PATH];
      subkey.get_string ("native", native_path, sizeof (native_path), "");
      if (strcasecmp(native_path,buf))
      {  // vielleicht als user anlegen?
         printf("mount / '%s'!='%s'\n",buf,native_path);
      }
   }


// PATH
   putenv("PGDATA=/usr/share/postgresql/data");                                                           
   
      /* chdir("cygwin\\bin"); */
//      int ipc_pid=spawnl(_P_NOWAIT,"cygwin\\bin\\ipc-daemon","ipc-daemon",NULL);
//      int pgsql_pid=spawnl(_P_NOWAIT,"cygwin\\bin\\postmaster","postmaster","-i",NULL);
      			// "-h","127.0.0.1"
      // putenv("PGHOST=127.0.0.1"); ?
//      spawnl(_P_WAIT,"midgard","midgard",NULL);
      // killen?
}
#endif

#include "launch_res.h"
#include <commctrl.h>

typedef  BOOL (*typefix)(HWND__ *, unsigned int, unsigned int, long int);

#if 0
BOOL WINAPI DialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{  switch (msg)
   {  
#if 0
      case WM_CLOSE:
         EndDialog(hwnd, 0); 
         return TRUE;
#endif
      default:
         return DefWindowProc(hwnd, msg, wParam, lParam);
   }
}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{  //INITCOMMONCONTROLSEX ice;
   //ice.dwSize = sizeof ice;
   //ice.dwICC  = 0; // ICC_TREEVIEW_CLASSES |ICC_LISTVIEW_CLASSES | ICC_TAB_CLASSES ;
   
   InitCommonControls(); // Ex(&ice);
   DialogBox(hInstance, MAKEINTRESOURCE(IDD_WELCOME_PAGE), 0, (typefix)&DefWindowProc);
   MessageBox(hInstance, "Test 1", "Test 2", MB_OK | MB_ICONASTERISK);
   return 0;
}
