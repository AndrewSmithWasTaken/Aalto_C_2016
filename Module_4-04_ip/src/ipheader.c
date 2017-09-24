#include <stdio.h>
#include <arpa/inet.h>
#include "ipheader.h"


/* Parses the given buffer into an IP header structure.
 * 
 * Parameters:
 * ip: pointer to the IP header structure that will be filled based
 *      on the data in the buffer
 * buffer: buffer of 20 bytes that contain the IP header. */
void parseIp(struct ipHeader *ip, const void *buffer)
{
    uint8_t *b = buffer;
    ip->version = (b[0] & 0xf0) >> 4;
    ip->ihl = (b[0] & 0x0f) * 4;
    ip->dscp = (b[1] & 0xfc) >> 2;
    ip->ecn = (b[1] & 0x3);
    ip->length = (b[2] << 8) | b[3];
    ip->identification = (b[4] << 8) | b[5];
    ip->flags = (b[6] & 0xE0) >> 5;
    ip->fragment_offset = ((b[6] & 0x1f) * 0x100) + (b[7]);
    ip->time_to_live = b[8];
    ip->protocol = b[9];
    ip->header_checksum = (b[10] << 8) + b[11];
    ip->source_ip[0] = b[12];
    ip->source_ip[1] = b[13];
    ip->source_ip[2] = b[14];
    ip->source_ip[3] = b[15];
    ip->destination_ip[0] = b[16];
    ip->destination_ip[1] = b[17];
    ip->destination_ip[2] = b[18];
    ip->destination_ip[3] = b[19];
}


/* Builds a 20-byte byte stream based on the given IP header structure
 * 
 * Parameters:
 * buffer: pointer to the 20-byte buffer to which the header is constructed
 * ip: IP header structure that will be packed to the buffer */
void sendIp(void *buffer, const struct ipHeader *ip)
{
    uint8_t *b = buffer;
    b[0] = (ip->version << 4) + ((ip->ihl) / 4);
    b[1] = (ip->dscp << 2) + (ip->ecn);
    b[2] = ip->length >> 8;
    b[3] = ip->length & 0x00ff;
    b[4] = ip->identification >> 8;
    b[5] = ip->identification & 0x00ff;
    b[6] = (ip->flags << 5) + (ip->fragment_offset >> 8);
    b[7] = ip->fragment_offset & 0x0ff;
    b[8] = ip->time_to_live;
    b[9] = ip->protocol;
    b[10] = ip->header_checksum >> 8;
    b[11] = ip->header_checksum & 0x00ff;
    b[12] = ip->source_ip[0];
    b[13] = ip->source_ip[1];
    b[14] = ip->source_ip[2];
    b[15] = ip->source_ip[3];
    b[16] = ip->destination_ip[0];
    b[17] = ip->destination_ip[1];
    b[18] = ip->destination_ip[2];
    b[19] = ip->destination_ip[3];
}


/* Prints the given IP header structure */
void printIp(const struct ipHeader *ip)
{
    /* Note: ntohs below is for converting numbers from network byte order
     to host byte order. You can ignore them for now
     To be discussed further in Network Programming course... */
    printf("version: %d   ihl: %d   dscp: %d   ecn: %d\n",
            ip->version, ip->ihl, ip->dscp, ip->ecn);
    printf("length: %d   id: %d   flags: %d   offset: %d\n",
            ntohs(ip->length), ntohs(ip->identification), ip->flags, ip->fragment_offset);
    printf("time to live: %d   protocol: %d   checksum: 0x%04x\n",
            ip->time_to_live, ip->protocol, ntohs(ip->header_checksum));
    printf("source ip: %d.%d.%d.%d\n", ip->source_ip[0], ip->source_ip[1],
            ip->source_ip[2], ip->source_ip[3]);
    printf("destination ip: %d.%d.%d.%d\n", ip->destination_ip[0],
            ip->destination_ip[1],
            ip->destination_ip[2], ip->destination_ip[3]);    
}

/* Shows hexdump of given data buffer */
void hexdump(const void *buffer, unsigned int length)
{
    const unsigned char *cbuf = buffer;
    unsigned int i;
    for (i = 0; i < length; ) {
        printf("%02x ", cbuf[i]);
        i++;
        if (!(i % 8))
            printf("\n");
    }
}
