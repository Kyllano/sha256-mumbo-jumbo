#include "sha256.h"

int main(int argc, char const *argv[])
{
    unsigned char str [] = "chocolatine";
    u_int64_t lenght_message_block;
    u_int32_t lenght_message_schedule;

    unsigned char * message_block = str_to_message_block(str, &lenght_message_block);
    //print_message_block(message_block, lenght_message_block);

    u_int32_t* message_schedule = create_message_schedule(message_block, &lenght_message_schedule, lenght_message_block);
    //print_message_schedule(message_schedule, lenght_message_schedule);
    change_message_schedule_endian(message_schedule, lenght_message_schedule);
    //printf("lenght : %d\n", lenght_message_schedule);
    
    u_int32_t* sha = compute_sha(message_schedule, lenght_message_schedule);


    printf("sha256");
    for (int i=0; i < 8; i++){
        printf("%08x",sha[i]);
    }
    printf("\n");
/*
    phase1(message_schedule, lenght_message_schedule);
*/



/*
    //TEST BLOCK FOR SIGMA lowercase VALUES
    //everything in message_schedule is in big endian
    //to compute sigma0 and sigma1, we need to put them back in little endian
    u_int32_t w0 = message_schedule[1];
    w0 = endian_converter(w0);
    u_int32_t wout0 = sigma0(w0);
    printf("\ncalcul sigma0 :\n0x%08x\n0x%08x\n", w0, wout0);

    u_int32_t w1 = message_schedule[15];
    w1 = endian_converter(w1);
    u_int32_t wout1 = sigma1(w1);
    printf("\ncalcul sigma1 :\n0x%08x\n0x%08x\n", w1, wout1);
*/
    
    
    free(sha);
    free(message_schedule);
    free(message_block);
    return 0;
}
