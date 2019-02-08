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

### Dumping Packets
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
This is just a way to decode the packets sent good-ol hexdump style.

#### Getting started
What you want to do is to:
```
socket -> setsockopt -> (set host) and bind -> listen -> accept -> accpet -> ... -> close
```

``` C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys.socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "error.h"
#include "dump.h"

#define PORT 7890 // The port we use

int main(void) {
    int sockfd, new_sockfd; // Listen on sock_fd, new connection new_fd
    struct sockaddr_in host_addr, client_addr; // My address information
    socklen_t sin_size;
    int recv_length=1, yes=1;
    char buffer[1024];

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal("in socket"); // exit if

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        fatal("setting socket option SO_REUSEADDR");
```
the socket function returns a socket file descriptor (EVERYTHING IN UNIX IS A FILE) the parameters are:
 * PF_INET: the domain of protocol this one is the TCP/IP family of the domain IPv4
 * SOCK_STREAM = TCP
 * 0 = there is only one protocol in PF_INET

setsockopt sets the socket options (like it sounds)
 * sockfd =  that CRITICAL socket file descriptor
 * SO_REUSEADDR = true so it will allow socket to reuse a given address binding
  * Also bullies other connections on this port (usually non closed programs) from using this port so it can
 * SOL_SOCKET = specifies the type of SO_REUSEADDR
 * &yes = pointer to data that the option should be set
 * sizeof(1) = size of &yes

### Bind and listen

``` C
host_addr.sin_family = AF_INET; // Host byte order
host_addr.sin_port = htons(PORT); // Short, network byte order
host_addr.sin_addr.s_addr = 0; // Automatically fill with my IP.
memset(&(host_addr.sin_zero), '\0', 8); // Zero the rest of the struct

if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
    fatal("binding to socket");

if (listen(sockfd, 5) == -1)
    fatal("listening on socket");
```
the `host_addr` is a the struct `sockaddr_in` this is just filling that struct the comments should be explainitory

bind binds the socket to a local address so it can listen for incoming connections (ret 0 on success and -1 on error)
 * sockfd = that looks familiar
 * that filled host_addr info make struct pointer
 * sizeof that pointer

*(Hey this all looks familiar kind of like my (CS 449) project)a*

listen function waits to connect and flow into accept loop
 * sockfd (you again)
 * 5 = places incoming connections into a backlog queue until an accept is called of this size

### How about that accept
``` C
while(1) { // Accept loop
    sin_size = sizeof(struct sockaddr_in);
    new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
    if(new_sockfd == -1)
        fatal("accepting connection");
    printf("server: got connection from %s port %d\n",
            inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    send(new_sockfd, "Hello, world!\n", 13, 0);
    recv_length = recv(new_sockfd, &buffer, 1024, 0);
    while(recv_length > 0) {
        printf("RECV: %d bytes\n", recv_length);
        dump(buffer, recv_length);
        recv_length = recv(new_sockfd, &buffer, 1024, 0);
    }
    close(new_sockfd);
}
```
AN ACCEPT LOOOOOOP!!!! The accept function takes in requests from a port and ip and creates a file descriptor from it.

Here we can `sendline` and `recv`. This is the networking

Good Job. We made a network 
