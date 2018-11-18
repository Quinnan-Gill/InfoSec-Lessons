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
    struct FID *ROOT_FID;
    struct FID *NULL_FID;
    char *KEY;
    char *PARENT_DIR;
    char *ROOT_DIR;
    long LONG_EXPIRE_TIME;

    char *VENUS_DIR;
    char *CALLBACK_PROMISE_EXT;
} Parameter = {
    {
        {2157}, // PORT
        {"127.0.0.1"}, // IP
        {"rmi:\/\/127.0.0.1:2157\/vice"}, // RMI_URL
        {12}, // FILE_BLOCK_NAME_LEN
        {64}, // FILE_ITEM_LEN
        {52}, // FILE_NAME_LEN
        {"D:\/\/afs.server\/"}, // VICE_DIR
        {
            {0, -1} // ROOT_FID
        },
        {
            {0, 0} // NULL_FID
        },
        {"19920256"}, // KEY
        {".."}, // PARENT_DIR
        {"/"}, //
        {30 * 60 * 1000}, // LOCK_EXPIRE_TIME
        {"D:\/afs.client.%d\/"}, // VENUS_DIR
        {".cp"} // CALLBACK_PROMISE_EXT
    }
};
