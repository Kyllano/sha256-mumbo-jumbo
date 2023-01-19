#include "sha256.h"

void print_hex_string(unsigned char* str){
    int i=0;
    int j=0;
    while (str[i] != '\0'){
        printf("%#02x ", str[i]);
        i++;
        j++;
        if (j == 8){
            j = 0;
            printf("\n");
        }
    }
    printf("\n");
}

void print_digest(unsigned char* digest){
    size_t lenght = strlen((char*) digest);
    u_int64_t i = 0;
    int j=0;
    while (i < (512/8)){
        printf("%#02x ", digest[i]);
        i++;
        j++;
        if (j == 8){
            j = 0;
            printf("\n");
        }
    }
    printf("\n");
}

unsigned char* str_to_padded(unsigned char* str){
    u_int64_t string_lenght = 0;
    while (str[string_lenght] != '\0') string_lenght ++; //We compute the lenght of our string
    string_lenght *= 8; //Each char is 8 bits
    u_int64_t full_lenght = string_lenght + 64; //The 64 bit long number to indicate the lenght of our string
    u_int64_t number_of_0_to_pad = 512 - (full_lenght % 512);

    //We allocate the pre_digest space
    unsigned char* pre_digest = (unsigned char*) malloc (sizeof(unsigned char) * ((full_lenght+number_of_0_to_pad)/8));

    //We rewrite the string char by char
    for (u_int64_t i=0; i < (string_lenght)/8; i++) pre_digest[i] = str[i];
    //Then we pad all the 0s needed
    for (u_int64_t i=(string_lenght)/8; i < (string_lenght + number_of_0_to_pad)/8; i++) pre_digest[i] = 0x00;
    //Finally, we put the 64 bit number at the end
    for (int i = 0; i < 8; i++){
        //very hacky, we copy byte by byte the lenght of the string (by shifting the bits to the right and each time only keeping the byte that we need)
        pre_digest[((string_lenght+number_of_0_to_pad)/8) + i] = (string_lenght >> ((7*8) - (i*8))) & 0xff; 
    }
    
    return pre_digest;
}