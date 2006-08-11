#include "CopyFile.hh"

using namespace std;
#define BUFF_SIZE 10240

int myCopyFile(const std::string &inFile, const std::string &outFile)
{
   char buff[BUFF_SIZE];
   int readBytes = 1;

   ifstream inFileStream(inFile.c_str(), ios::in|ios::binary);
   if(!inFileStream)
   {
     cerr << "Coudn't open infile "<<inFile<<'\n';
     return -1;
   }
#if 0
   ifstream tmpStream(outFile.c_str());
   if(tmpStream)
   {
      cerr << "Coudn't open outfile "<<outFile<<'\n';
      return -1;
   }
   tmpStream.close();
#endif
   ofstream outFileStream(outFile.c_str(), ios::out|ios::binary);
   if(!outFileStream)
   {
     cerr << "Coudn't open outfile "<<outFile<<'\n';
     return -1;
   }

   while(readBytes != 0)
   {
     inFileStream.read((char*)buff, BUFF_SIZE);
     readBytes = inFileStream.gcount();
     outFileStream.write((char*)buff, readBytes);
   }
   return 0;
}
