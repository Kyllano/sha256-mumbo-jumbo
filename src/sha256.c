#include "sha256.h"

    u_int32_t k[64] =
   {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    u_int32_t h[8] =
   {0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};


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


void print_message_block(unsigned char* message_block, u_int64_t message_block_lenght){
    //size_t lenght = strlen((char*) message_block);
    u_int64_t i = 0;
    int j=0;
    while (i < (message_block_lenght)){
        printf("0x%02x ", message_block[i]);
        i++;
        j++;
        if (j == 8){
            j = 0;
            printf("\n");
        }
    }
    printf("\n");
}

u_int32_t endian_converter(u_int32_t num){
    u_int32_t b0,b1,b2,b3;
    u_int32_t res;

    b0 = (num & 0x000000ff) << 24u;
    b1 = (num & 0x0000ff00) << 8u;
    b2 = (num & 0x00ff0000) >> 8u;
    b3 = (num & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;
    return res;
}

void print_message_schedule(u_int32_t* message_schedule){
    int j=0;
    for (int i = 0; i < 64; i++){
        //The number we get
        //printf("\n->%d\n0x%08x\n", message_schedule[i] ,message_schedule[i]);
        //how it really is in memory
        for (int j = 0; j < 4; j++){
            u_int32_t toPrint = message_schedule[i];
            toPrint = (toPrint >> (j*8)) & 0x000000ff;
            printf("0x%02x ", toPrint) ;
        }
        j++;
        if (j==2){
            j = 0;
            printf("\n");
        }
    }
}

u_int32_t sig0 (u_int32_t w){
    u_int32_t w1 = w >> 7  | w << 25;
    u_int32_t w2 = w >> 18 | w << 14;
    u_int32_t w3 = w >> 3;

    u_int32_t wout = w1 ^ w2 ^ w3;

    return wout;
}

u_int32_t sig1 (u_int32_t w){
    u_int32_t w1 = w >> 17 | w << 15;
    u_int32_t w2 = w >> 19 | w << 13;
    u_int32_t w3 = w >> 10;

    u_int32_t wout = w1 ^ w2 ^ w3;

    return wout;
}

u_int32_t SIG0 (u_int32_t w){
    u_int32_t w1 = w >> 2  | w << 30;
    u_int32_t w2 = w >> 13 | w << 19;
    u_int32_t w3 = w >> 22 | w << 10;

    u_int32_t wout = w1 ^ w2 ^ w3;

    return wout;
}

u_int32_t SIG1 (u_int32_t w){
    u_int32_t w1 = w >> 6  | w << 26;
    u_int32_t w2 = w >> 11 | w << 21;
    u_int32_t w3 = w >> 25 | w << 7 ;

    u_int32_t wout = w1 ^ w2 ^ w3;

    return wout;
}

u_int32_t choice (u_int32_t a, u_int32_t b, u_int32_t c){
    u_int32_t w1 = a & b;
    u_int32_t w2 = (~a) & c;
    
    u_int32_t wout = w1 ^ w2;

    return wout;
}

u_int32_t maj (u_int32_t a, u_int32_t b, u_int32_t c){
    u_int32_t w1 = a & b;
    u_int32_t w2 = a & c;
    u_int32_t w3 = b & c;
    
    u_int32_t wout = w1 ^ w2 ^w3;

    return wout;
}


//Will return a char array conaining the string padded with zeros with the lenght of the string at the end. Also gives the complete lenght of the pre message_block in u_int64_t* lenght
unsigned char* str_to_message_block(unsigned char* str, u_int64_t* lenght){
    u_int64_t string_lenght = 0;
    while (str[string_lenght] != '\0') string_lenght ++; //We compute the lenght of our string
    string_lenght *= 8; //Each char is 8 bits
    u_int64_t full_lenght = string_lenght + 64; //The 64 bit long number to indicate the lenght of our string
    u_int64_t number_of_0_to_pad = 512 - (full_lenght % 512);

    //We allocate the message block space (The +1 is for the single 1 we have to add to the string)
    unsigned char* message_block = (unsigned char*) malloc (sizeof(unsigned char) * (((full_lenght+number_of_0_to_pad)/8) + 1));

    //We rewrite the string char by char
    for (u_int64_t i=0; i < (string_lenght)/8; i++) {
        message_block[i] = str[i];
    }
    message_block[string_lenght/8] = 0b10000000; //We append the 1 to the string
    //Then we pad all the 0s needed
    for (u_int64_t i=((string_lenght)/8)+1; i < (string_lenght + number_of_0_to_pad)/8; i++) message_block[i] = 0x00;
    //Finally, we put the 64 bit number at the end
    for (int i = 0; i < 8; i++){
        //very hacky, we copy byte by byte the lenght of the string (by shifting the bits to the right and each time only keeping the byte that we need)
        u_int64_t j = ((string_lenght+number_of_0_to_pad)/8) + i;
        message_block[j] = (string_lenght >> ((7*8) - (i*8))) & 0xff;
    }
    //We return the lenght in bytes
    *lenght = (full_lenght + number_of_0_to_pad)/8; 
    return message_block;
}


/*
ATTNETION, ICI J MET UN TABLEAU DE 64, A CHANGER!!!!
*/
u_int32_t* create_message_schedule(unsigned char* message_block, u_int32_t* lenght_message_schedule){
    //printf("lol : %ld\n", sizeof(char));
    //int lenght = sizeof(u_int32_t) * 64;
    //printf("TAILLE : %d\n", lenght);
    u_int32_t* message_schedule = (u_int32_t*) malloc(sizeof(u_int32_t) * 64);
    *lenght_message_schedule = 64*4;

    memcpy(message_schedule, message_block, 64);
    memset(&(message_schedule[16]), 0x00, 192);
    return message_schedule;
}


//lenght must be in bytes
void phase1 (u_int32_t* message_schedule, u_int64_t lenght){
    lenght /= 4;

    printf("ON EST LA : %ld\n", lenght);

    for (int i=16; i < lenght; i++){
        u_int32_t w1 = endian_converter(message_schedule[i-16]);
        u_int32_t w2 = endian_converter(sig0(message_schedule[i-15]));
        u_int32_t w3 = endian_converter(message_schedule[i-7]);
        u_int32_t w4 = endian_converter(sig1(message_schedule[i-2])); 
        message_schedule[i] = endian_converter(w1+w2+w3+w4);
        printf("%d : 0x%08x\n", i, message_schedule[i]);
    }
}
