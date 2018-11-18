#include <stdio.h>
#include <stdlib.h>

struct FID {
    unsigned long userId;
    signed int uniquifier;
};

struct FileAttributes {
    unsigned long createTime;
    unsigned long modifiedTime;
    unsigned long creatorId;
    unsigned long modifierId;
    unsigned int fileSize;
    struct FID *parentDir;
};

struct FileHandler {
    struct FileAttributes *attributes;
    char *data;
};

enum LockMode {
    SHARED,
    EXCLUSIVE
};

struct Lock {
    unsigned long userId;
    unsigned long requestTime;
    struct FID *fid;
    enum LockMode mode;
};

struct Parameter{
    int PORT;
    char *IP;
    char *RMI_URL;

    int FILE_BLOCK_NAME_LEN;
    int FILE_ITEM_LEN;
    int FILE_NAME_LEN;

    char *VICE_DIR;
    struct FID

    const int PORT = 2157;
    const char IP[] = "127.0.0.1";
    char *RMI_URL;
    sprintf(RMI_URL,  "rmi:\/\/%s:%d\/vice", PORT, IP);

    const int FILE_BLOCK_NAME_LEN = 12;
    const int FILE_ITEM_LEN = 64;
    const int FILE_NAME_LEN = FILE_ITEM_LEN - FILE_BLOCK_NAME_LEN;

    const char VICE_DIR[] = "D:\/\/afs.server\/";
    struct FID *ROOT_FID = (struct FID*)malloc(sizeof(struct FID));
    ROOT_FID->userId = 0;
    ROOT_FID->uniquifier = -1;

    struct FID *NULL_FID = (struct FID*)malloc(sizeof(struct FID));
    NULL_FID->userId = 0;
    NULL_FID->uniquifier = 0;

    const char KEY[] = "19920256";
    const char PARENT_DIR[] = "..";
    const char ROOT_DIR[] = "/";
    const long LONG_EXPIRE_TIME = 30 * 60 * 1000;

    const char VENUS_DIR[] = "D:\/afs.client.%d\/";
    const char CALLBACK_PROMISE_EXT[] = ".cp";
} Parameter;
