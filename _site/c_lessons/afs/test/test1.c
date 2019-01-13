#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

typedef unsigned char byte;

int main() {
    byte arr[3] = {0x41, 0x42, 0x43};

    for(int i=0; i < 3; i++) {
        printf("%c\n", arr[i]);
    }
}
