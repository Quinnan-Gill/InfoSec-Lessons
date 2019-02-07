# Networking

## OSI Model

***Physical Layer*** Bitstreams

***Data-Link Layer*** Mac Addresses and 801.11x protocol

***Network Layer*** IP

***Tansport Layer*** TCP/UDP

***Session Layer*** Used to establish and maintain connection

***Presentation Layer*** Encryption and data compression

***Application Layer*** HTTP

## Sockets

***Stream Sockets*** two-way communication similar to when you call someone on
the phone (TCP or Transmission Control Protocol)

***Datagram Socket*** Like sending a text. UDP or User Datagram Protocol exists
here. Good for streaming video. Little overhead and packet loss is exceptable

## Simple Server

``` C
// Dumps raw memory in hex byte and printable split format
void dump(const unsigned char *data_buffer, const unsigned int length) {
    unsigned char byte;
    unsigned int i, j;
    for(i=0; i < length; i++) {
        byte = data_buffer[i];
        printf("%02x ", data_buffer[i]); // Display byte in hex
        if(((i%16)==15) || (i==length-1)) {
            for(j=0; j < 15-(i%16); j++)
                printf("   ");
            printf("| ");
            for(j=(i-(i%16)); j <= i; j++) { // Display printable bytes from line
                byte = data_buffer[j];
                if((byte > 31) && (byte < 127)) // Outside printable char range
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n"); // End of the dump line (each line is 16 bytes)
        }
    }
}
```
