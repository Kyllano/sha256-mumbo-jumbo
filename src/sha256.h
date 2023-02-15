#ifndef __SHA256__
#define __SHA256__

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


void print_hex_string(unsigned char* str);
void print_message_block(unsigned char* message_block, u_int64_t message_block_lenght);
unsigned char* str_to_message_block(unsigned char* str, u_int64_t* lenght);
u_int32_t* create_message_schedule(unsigned char* message_block, u_int32_t* lenght_message_schedule);
void print_message_schedule(u_int32_t* message_schedule);
u_int32_t endian_converter(u_int32_t num);


u_int32_t sig0 (u_int32_t w);
u_int32_t sig1 (u_int32_t w);
u_int32_t SIG0 (u_int32_t w);
u_int32_t SIG1 (u_int32_t w);
u_int32_t choice (u_int32_t w, u_int32_t a, u_int32_t b);
u_int32_t maj (u_int32_t w, u_int32_t a, u_int32_t b);

void phase1 (u_int32_t* message_block, u_int64_t lenght);

#endif