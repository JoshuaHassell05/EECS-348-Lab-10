#include <iostream>
#include <fstream>
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
void add_strings(const char* A, const char* B, char sum_out[2048]) {
    bool sign_A = false, sign_B = false;
    char int_A[512], frac_A[512], int_B[512], frac_B[512];
    parse_valid(A, sign_A, int_A, frac_A);
    parse_valid(B, sign_B, int_B, frac_B);
    int frac_len_A = my_len(frac_A);
    int frac_len_B = my_len(frac_B);
    int common_frac_len = (frac_len_A > frac_len_B) ? frac_len_A : frac_len_B;
    char big_A[2048], big_B[2048];
    int write_pos = 0;
    for (int i = 0; int_A[i] != '\0'; ++i) big_A[write_pos++] = int_A[i];
    for (int k = 0; k < common_frac_len; ++k) big_A[write_pos++] = (k < frac_len_A ? frac_A[k] : '0');
    big_A[write_pos] = '\0';
    write_pos = 0;
    for (int i = 0; int_B[i] != '\0'; ++i) big_B[write_pos++] = int_B[i];
    for (int k = 0; k < common_frac_len; ++k) big_B[write_pos++] = (k < frac_len_B ? frac_B[k] : '0');
    big_B[write_pos] = '\0';
    int len_A = my_len(big_A), len_B = my_len(big_B);
    int cmp_mag = 0;
    if (len_A != len_B) {
        cmp_mag = (len_A < len_B) ? -1 : 1;
    } else {
        for (int i = 0; i < len_A; ++i) {
            if (big_A[i] != big_B[i]) { cmp_mag = (big_A[i] < big_B[i]) ? -1 : 1; break; }
        }
    }
    bool sign_result = false;
    char mag_result[2048]; mag_result[0] = '\0';
    if (sign_A == sign_B) {
        int i = len_A - 1, j = len_B - 1, carry = 0, rpos = 0;
        char rev_buf[2048];
        while (i >= 0 || j >= 0 || carry) {
            int da = (i >= 0) ? (big_A[i] - '0') : 0;
            int db = (j >= 0) ? (big_B[j] - '0') : 0;
            int s = da + db + carry;
            rev_buf[rpos++] = char('0' + (s % 10));
            carry = s / 10;
            --i; --j;
        }
        for (int k = 0; k < rpos; ++k) mag_result[k] = rev_buf[rpos - 1 - k];
        mag_result[rpos] = '\0';
        sign_result = sign_A;
    } else {
        const char* X = big_A;
        const char* Y = big_B;
        sign_result = sign_A;
        if (cmp_mag == 0) {
            sum_out[0] = '0'; sum_out[1] = '\0';
            return;
        } else if (cmp_mag < 0) {
            X = big_B; Y = big_A;
            sign_result = sign_B;
        }
        int i = my_len(X) - 1, j = my_len(Y) - 1, borrow = 0, rpos = 0;
        char rev_buf[2048];
        while (i >= 0) {
            int dx = (X[i] - '0') - borrow;
            int dy = (j >= 0) ? (Y[j] - '0') : 0;
            if (dx < dy) { dx += 10; borrow = 1; } else borrow = 0;
            rev_buf[rpos++] = char('0' + (dx - dy));
            --i; --j;
        }
        while (rpos > 0 && rev_buf[rpos - 1] == '0') --rpos;
        for (int k = 0; k < rpos; ++k) mag_result[k] = rev_buf[rpos - 1 - k];
        mag_result[rpos] = '\0';
        if (mag_result[0] == '\0') { mag_result[0] = '0'; mag_result[1] = '\0'; sign_result = false; }
    }
    int mag_len = my_len(mag_result);
    int int_len = (mag_len > common_frac_len) ? (mag_len - common_frac_len) : 0;

    char int_part[1024]; int ip = 0;
    if (int_len == 0) int_part[ip++] = '0';
    else for (int i = 0; i < int_len; ++i) int_part[ip++] = mag_result[i];
    int_part[ip] = '\0';
    int L = my_len(int_part), z = 0;
    while (z + 1 < L && int_part[z] == '0') ++z;
    if (z > 0) { int j = 0; while (z + j <= L) { int_part[j] = int_part[z + j]; ++j; } }
    char frac_part[1024]; int fp = 0;
    for (int i = int_len; i < mag_len; ++i) frac_part[fp++] = mag_result[i];
    frac_part[fp] = '\0';
    while (fp > 0 && frac_part[fp - 1] == '0') frac_part[--fp] = '\0';
    int out_pos = 0;
    if (!(int_part[0] == '0' && int_part[1] == '\0' && frac_part[0] == '\0') && sign_result)
        sum_out[out_pos++] = '-';
    for (int i = 0; int_part[i] != '\0'; ++i) sum_out[out_pos++] = int_part[i];
    if (frac_part[0] != '\0') {
        sum_out[out_pos++] = '.';
        for (int i = 0; frac_part[i] != '\0'; ++i) sum_out[out_pos++] = frac_part[i];
    }
    sum_out[out_pos] = '\0';
}
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
      if (!valid_A || !valid_B){                        
               if (!valid_A && !valid_B)                    
                  std::cout << "Line " << line << ": invalid numbers: \"" << A << "\" and \"" << B << "\"\n"; 
               else if (!valid_A)                      
                  std::cout << "Line " << line << ": invalid number: \"" << A << "\"\n"; 
               else                               
                  std::cout << "Line " << line << ": invalid number: \"" << B << "\"\n"; 
               continue;                         
      }
      char sum[2048];                       
      add_strings(A, B, sum);                
      std::cout << A << " + " << B << " = " << sum << "\n"; 
    }
   return 0;                                  
}