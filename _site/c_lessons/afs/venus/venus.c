#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *venusRMI;
    int venusRMIPort = 0;

    if (argc < 2) {
        printf("Arg Format Error: should be (%ip %port)");
        exit(-1);
    }
    venusRMIPort = argv[1];
    sprintf(venusRMI, "rmi://%s:%d/venus", argv[0], venusRMIPort);
}
