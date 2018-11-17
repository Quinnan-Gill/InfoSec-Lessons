#include <stdio.h>

struct parameter {
    const int PORT = 2157;
    const char IP[9] = "127.0.0.1";
    const char RMI_URL[28] = "rmi:\/\/127.0.0.1:2157\/vice";

    const int FILE_BLOCK_NAME_LEN = 12;
    const int FILE_ITEM_LEN = 64;
    const int FILE_NAME_LEN = FILE_ITEM_LEN - FILE_BLOCK_NAME_LEN;

    const char VICE_DIR[] = "D:\/\/afs.server\/";
    const int ROOT_FID =
}
