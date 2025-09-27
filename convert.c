#include <stdint.h>
#include <stdio.h>
#include <string.h>

/////////////////////////////////////////// oct_to_bin ///////////////////////////////////////////
void oct_to_bin(const char *oct, char *out)
{
    char temp[50];
    int pos = 0;
      
     // Handle zero case properly (string comparison)
    if (strcmp(oct, "0") == 0) {
        strcpy(out, "0");
        return;
    }
      for(int i = 0; i < strlen(oct); i++)
      {
      	  //Note const char *oct comes in as a "char" and not an "int"
      	  int digit = oct[i] - '0';  // convert char -> int
	  //determines which are 1 and 0s using 3 bit
          temp[pos++] = ((digit >> 2) & 1) ? '1' : '0';
          temp[pos++] = ((digit >> 1) & 1) ? '1' : '0';
          temp[pos++] = ((digit >> 0) & 1) ? '1' : '0';
      }
      for(int j = 0; j < strlen(temp); j++)
      {
         out[j] = temp[j];
      }
	out[pos] = '\0';
}
/////////////////////////////////////////// oct_to_hex ///////////////////////////////////////////
void oct_to_hex(const char *oct, char *out) {
    char temp[256];  // binary string
    int pos = 0;

    // Step 1: oct -> binary string
    for (int i = 0; i < strlen(oct); i++) {
        int digit = oct[i] - '0';// convert char -> int
	//determines which are 1 and 0s using 3 bit
        temp[pos++] = ((digit >> 2) & 1) ? '1' : '0';
        temp[pos++] = ((digit >> 1) & 1) ? '1' : '0';
        temp[pos++] = ((digit >> 0) & 1) ? '1' : '0';
    }
    temp[pos] = '\0';

    // Step 2: pad binary string at front so length % 4 == 0
    int len = strlen(temp);
    int pad = (4 - (len % 4)) % 4;
    char padded[260];
    int k = 0;
    for (int i = 0; i < pad; i++) padded[k++] = '0';
    for (int i = 0; i < len; i++) padded[k++] = temp[i];
    padded[k] = '\0';

    // Step 3: process 4 bits at a time -> hex
    int outpos = 0;
    for (int i = 0; i < k; i += 4) {
        int value = (padded[i]   - '0') * 8 +
                    (padded[i+1] - '0') * 4 +
                    (padded[i+2] - '0') * 2 +
                    (padded[i+3] - '0') * 1;
        if (value < 10) out[outpos++] = '0' + value;
        else out[outpos++] = 'A' + (value - 10);
    }
    out[outpos] = '\0';  // <- IMPORTANT: terminate before touching `out`

    // Remove leading zeros but keep a single '0' if the whole string is zero
    char *p = out;
    while (*p == '0' && *(p+1) != '\0') p++;    // move to first non-zero (or last char)
    if (p != out) memmove(out, p, strlen(p) + 1); // shift remainder left, including '\0'
}
/////////////////////////////////////////// hex_to_bin ///////////////////////////////////////////
void hex_to_bin(const char *hex, char *out) {
    int outpos = 0;
    for (int i = 0; i < strlen(hex); i++) {
        char c = hex[i];
        int value;
	//finds the value
        if (c >= '0' && c <= '9') value = c - '0';
        else if (c >= 'A' && c <= 'F') value = 10 + (c - 'A');
        else if (c >= 'a' && c <= 'f') value = 10 + (c - 'a');
        else continue; // skip invalid chars

        // Convert to 4-bit binary
        out[outpos++] = (value & 8) ? '1' : '0';
        out[outpos++] = (value & 4) ? '1' : '0';
        out[outpos++] = (value & 2) ? '1' : '0';
        out[outpos++] = (value & 1) ? '1' : '0';
    }
    out[outpos] = '\0';
}
/////////////////////////////////////////// to_sign_magnitude /////////////////////////////////////
void to_sign_magnitude(int num, char *out) {
    int pos = 0;
    int x;
    //if it is a negative number
    if(num < 0)
        {
            x = num*-1;
            out[pos++] = '1'; //automatically starts the far right as 1
            for (int i = 30; i >= 0; i--) {    	
                out[pos++] = (x & (1 << i)) ? '1' : '0';
            }
        }
     //positive numbers
     else
        {
	    //runs for 32 bits
            for (int i = 31; i >= 0; i--) {    	
                out[pos++] = (num & (1 << i)) ? '1' : '0';
            }
        }
    
    // loop from most significant bit to least significant bit
    
    
    out[pos] = '\0';
}
/////////////////////////////////////////// to_ones_complement ///////////////////////////////////
void to_ones_complement(int num, char *out) {
    int pos = 0;
    int x;
    //if it is a negative number
    if(num < 0)
        {        
        	int x = num - 1; //helps align everythng
            for (int i = 31; i >= 0; i--) {    	
                out[pos++] = (x & (1 << i)) ? '1' : '0';
            }
        }
     //positive numbers
     else
        {
            for (int i = 31; i >= 0; i--) {    	
                out[pos++] = (num & (1 << i)) ? '1' : '0';
            }
        }   
    // loop from most significant bit to least significant bit
    
    
    out[pos] = '\0';
}
/////////////////////////////////////////// to_twos_complement ///////////////////////////////////
void to_twos_complement(int num, char *out) {
    int pos = 0;
    int x;
    //if it is a negative number
    if(num < 0)
        {        
        	num += 1; //adds 1 to the bit
        	int x = num - 1; //helps align everything
            for (int i = 31; i >= 0; i--) {    	
                out[pos++] = (x & (1 << i)) ? '1' : '0';
            }
        }
     //positive numbers
     else
        {
            for (int i = 31; i >= 0; i--) {    	
                out[pos++] = (num & (1 << i)) ? '1' : '0';
            }
        }
    
    // loop from most significant bit to least significant bit
    
    
    out[pos] = '\0';
}