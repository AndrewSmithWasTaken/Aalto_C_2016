#include "base64.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
/* The set of base64-encoded characters. You may use this table if you want.
 * (The last character is not part of the actual base64 set, but used for
 * padding).
 */
const char *encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
 
void encode(unsigned char *in, unsigned char *out, int len) {
    out[0] = encoding[in[0] >> 2];
    out[1] = encoding[((in[0] & 0x03) << 4) + (in[1] >> 4)];
    out[2] = (len > 1 ? encoding[((in[1] & 0x0f) << 2) + (in[2] >> 6)] : '=');
    out[3] = (len > 2 ? encoding[in[2] & 0x3f] : '=');
}
 
void decode(unsigned char *in, unsigned char *out) {
    for (int i = 0; i < 4; i++) {
        int j = 0;
        while (encoding) {
            if (in[i] == encoding[j]) {
                in[i] = j;
                break;
            }
            j++;
        }
    }
    out[0] = (in[0] << 2) + (in[1] >> 4);
    out[1] = (in[1] << 4) + (in[2] >> 2);
    out[2] = (in[2] << 6) + in[3];
}
 
/* Open file named <src_file> for reading, and convert it to Base64 format,
 * which is written to file named <dst_file>.
 *
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int to_base64(const char *dst_file, const char *src_file) {
    // Declare and initialise local variables
    int numBytes = 0;
    int n = 0;
    int len = 0;
    int blocks = 0;
    unsigned char in[3];
    unsigned char out[4];
    // IO operations with checks
    FILE *src = fopen(src_file, "r");
    if (!src) {
        return -1;
    }
    FILE *dst = fopen(dst_file, "w");
    if (!dst) {
        return -1;
    }
    // Loop through src and encode
    do {
        n = fread(in, sizeof(char), 3, src);
        if (!n) {
            break;
        }
        for (int i = 0; i < 3; i++) {
            if (i + 1 <= n) {
                len++;
            }
            else {
                in[i] = '\0';
            }
        }
        numBytes += n;
        if (len > 0) {
            encode(in, out, len);
            int f = fwrite(out, sizeof(char), 4, dst);
            blocks += f;
            if (blocks == 64) {
                fprintf(dst, "\n");
                blocks = 0;
            }
            len = 0;
        }
    } while (1);
    // Close IO streams, return number of bytes read
    fclose(src);
    fclose(dst);
    return numBytes;
}
 
/* Open Base64-encoded file named <src_file> for reading, and convert it
 * to regular binary format, which is written to file named <dst_file>.
 *
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int from_base64(const char *dst_file, const char *src_file) {
    int numBytes = 0;
    unsigned char in[4];
    unsigned char out[3];
    FILE *src = fopen(src_file, "r");
    if (!src) {
        return -1;
    }
    FILE *dst = fopen(dst_file, "w");
    if (!dst) {
        return -1;
    }
    while (!feof(src)) {
        if (numBytes % 65 == 64 && numBytes != 0) {
            fgetc(src);
            numBytes++;
        }
        numBytes += fread(in, sizeof(char), 4, src);
        if (!feof(src)) {
            decode(in, out);
            int number_of_equals = 0;
            int decoded_bytes = 0;
            for (int i = 0; i < 3; i++) {
                if (out[i] == 64) {
                    number_of_equals += 1;
                }
            }
            if (number_of_equals == 1) {
                decoded_bytes = 2;
            }
            else if (number_of_equals == 2) {
                decoded_bytes = 1;
            }
            else decoded_bytes = 3;
            for (int i = 0; i < decoded_bytes; i++) {
                putc(out[i], dst);
            }
        }
    }
    fclose(src);
    fclose(dst);
    return numBytes;
}
