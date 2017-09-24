#ifndef AALTO_MACHDR_H
#define AALTO_MACHDR_H

int get_proto_version(const unsigned char *header);
int get_type(const unsigned char *header);
int get_subtype(const unsigned char *header);
int get_to_ds(const unsigned char *header);
int get_from_ds(const unsigned char *header);
int get_retry(const unsigned char *header);
int get_more_data(const unsigned char *header);

void set_proto_version(unsigned char *header, int version);
void set_type(unsigned char *header, int type);
void set_subtype(unsigned char *header, int subtype);
void set_to_ds(unsigned char *header, int flag);
void set_from_ds(unsigned char *header, int flag);
void set_retry(unsigned char *header, int flag);
void set_more_data(unsigned char *header, int flag);

#endif

//get_proto_version that will return the protocol version from the header (should return integer values 0-3)
//
//get_type that will return the frame type (integer values 0-3)
//
//get_subtype that will return frame subtype (integer values 0-15)
//
//get_to_ds, get_from_ds, get_retry, get_more_data that will return these respective flags from header. Any non-zero value will be considered as set flag, and zero value means an unset flag.