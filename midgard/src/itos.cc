#include "itos.h"
#include <cstdio>

string itos(int i)
{
 char buffer[100];
 snprintf(buffer,sizeof buffer,"%i",i);
 return(buffer);
}
