#include "machdr.h"
#include <string.h>

/* a) Implement all get_* functions. <header> points to the start of the
 * MAC header. The functions return the value of the respective field.
 * For flags, any non-zero return value indicates that flag is set, and zero
 * means it is not set.
 */

int get_proto_version(const unsigned char *header)
{
    unsigned char byte_one = header[0];
    return byte_one >> 6;
}

int get_type(const unsigned char *header)
{
    unsigned char byte_one = header[0];
    return (byte_one >> 4) & 0x3;
}

int get_subtype(const unsigned char *header)
{
    unsigned char byte_one = header[0];
    return byte_one & 0xf;
}

int get_to_ds(const unsigned char *header)
{
    unsigned char byte_two = header[1];
    //unsigned int v = byte_two & 0x80;
    return byte_two & 0x80;
}

int get_from_ds(const unsigned char *header)
{
    unsigned char byte_two = header[1];
    return byte_two & 0x40;
}

int get_retry(const unsigned char *header)
{
    unsigned char byte_two = header[1];
    return byte_two & 0x10;
}

int get_more_data(const unsigned char *header)
{
    unsigned char byte_two = header[1];
    return byte_two & 0x4;
}

/* b) Implement all set_* functions that set the values of respective
 * fields in the MAC header. <header> points to the start of the header,
 * and the second parameter indicates the value to be set.
 */

void set_proto_version(unsigned char *header, int version)
{
    header[0] = (version << 6) + (header[0] & 0x3f);
}

void set_type(unsigned char *header, int type)
{
    header[0] = (type << 4) + (header[0] & 0xcf);
}

void set_subtype(unsigned char *header, int subtype)
{
    header[0] = subtype + (header[0] & 0xf0);
}

void set_to_ds(unsigned char *header, int flag)
{
    header[1] = (flag << 7) + (header[1] & 0x7f);
}

void set_from_ds(unsigned char *header, int flag)
{
    header[1] = (flag << 6) + (header[1] & 0xbf);
}

void set_retry(unsigned char *header, int flag)
{
    header[1] = (flag << 4) + (header[1] & 0xef);
}

void set_more_data(unsigned char *header, int flag)
{
    header[1] = (flag << 2) + (header[1] & 0xfb);
}
