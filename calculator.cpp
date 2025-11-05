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
      bool sign_A = false, sign_B = false;
      char int_A[512], frac_A[512], int_B[512], frac_B[512];
      bool valid_A = parse_valid(A, sign_A, int_A, frac_A);   
      bool valid_B = parse_valid(B, sign_B, int_B, frac_B);  
   }
   return 0;
}
int my_len(const char* s){ 
    int n = 0;            
    while (s[n] != '\0')   
        ++n;               
    return n;              
}
bool parse_valid(const char* raw, bool& neg, char int_out[512], char frac_out[512]){
   neg = false;
   int_out[0] = '\0';
   frac_out[0] = '\0';
   if (raw[0] == '\0'){
      return false;
   }
   int p = 0;
   if (raw[p] == '+' || raw[p] == '-'){
      neg = (raw[p] == '-');
      ++p;
      if (raw[p] == '\0'){
         return false;
      }
   }
   int dot = -1;
   for (int i = p; raw[i] != '\0'; ++i){
      if (raw[i] == '.'){
         if (dot != -1){
            return false;
         }
         dot = i;
      }
       else if (!(raw[i] >= '0' && raw[i] <= '9')){
         return false;
       }
      }
   int index_A = 0;
   int index_B = 0;                           
    if (dot == -1) {                      
        if (!(raw[p] >= '0' && raw[p] <= '9')) return false; 
        for (int i = p; raw[i] != '\0'; ++i) int_out[index_A++] = raw[i]; 
        int_out[index_A] = '\0';                  
        frac_out[0] = '\0';                  
    } else {                              
        if (dot == p){
         return false;
         }       
        if (raw[dot + 1] == '\0') return false; 
        for (int i = p; i < dot; ++i) int_out[index_A++] = raw[i]; 
        int_out[index_A] = '\0';                  
        for (int i = dot + 1; raw[i] != '\0'; ++i) frac_out[index_B++] = raw[i]; 
        frac_out[index_B] = '\0';                  
    }

    int int_length = my_len(int_out);               
    int k = 0;                            
    while (k + 1 < int_length && int_out[k] == '0') ++k; 
    if (k > 0) {                         
        int j = 0;                        
        while (k + j <= int_length) {             
            int_out[j] = int_out[k + j];       
            ++j;                          
        }
    }

    int frac_length = my_len(frac_out);               
    while (frac_length > 0 && frac_out[frac_length - 1] == '0'){
        frac_out[--frac_length] = '\0';                
    }
    if (int_out[0] == '0' && int_out[1] == '\0' && frac_out[0] == '\0'){
      neg = false; 
    }
    if (int_out[0] == '0' && int_out[1] == '\0' && frac_out[0] == '\0'){
      neg = false; 
    }
    return true;                         
}
   
