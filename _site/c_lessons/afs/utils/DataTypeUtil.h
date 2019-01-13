#ifndef DATA_TYPE_UTIL_H_
#define DATA_TYPE_UTIL_H_

typedef unsigned char byte;

byte *hexString2ByteArray(char *s, int length);

char *byteArray2HexString(byte *bytes, int length);

int byteArray2Int(byte *bytes, int length);

byte *int2ByteArray(int bytes);

long byteArray2Long(byte *bytes, int length);

byte *long2ByteArray(long bytes);

bool byteArrayEquals(byte *a1, int len1, byte *a2, )

#endif
