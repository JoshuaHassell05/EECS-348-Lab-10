#include <iostream>
#include <fstream>
int main(){
   char filename[256];
   std::cout << "Enter filename: ";
   std::cin >> filename;
   std ::ifstream in(filename);
   char A[1024], B[1000];
   int line = 0;
   while (in >> A >> B){
      ++line;
      bool Sign_A = false, Sign_B = false;
      char int_A[512], fract_A[512], int_B[512], fract[512];
   }
   return 0;
}