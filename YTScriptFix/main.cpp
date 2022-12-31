#include <fstream>
#include "TranscriptFix.h"
using namespace std;
using namespace sdds;

int main()
{
   ifstream readFile("script.txt");
   ofstream fixedFile("scriptFixed.txt");
   TranscriptFix transcript;

   readFile >> transcript;
   fixedFile << transcript;

   return 0;
}