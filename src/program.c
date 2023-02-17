#include "sha256.h"

int main(int argc, char const *argv[])
{
    unsigned char input [] = "Hi, How are ya?";
    unsigned char output [64];
    create_sha(input, output);
    printf("MON SHA : %s\n", output);
    return 0;
}
