#include "sha256.h"


int main(int argc, char const *argv[])
{
    unsigned char str [14] = "sha256 rocks!";
    unsigned char * pre_digest = str_to_padded(str);
    print_digest(pre_digest);
    free(pre_digest);
    return 0;
}
