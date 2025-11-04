#include <iostream>
#include <fstream>
int main(){
   char filename[256];
   std::cout << "Enter filename: ";
   std::cin >> filename;
   std ::ifstream fin(filename);
   

   return 0;
}