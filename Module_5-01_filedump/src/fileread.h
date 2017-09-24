#ifndef AALTO_FILEREAD_H
#define	AALTO_FILEREAD_H

int textdump(const char *filename);
int hexdump(const char *filename);

#endif	/* AALTO_ANYDATA_H */


//Objective: Practice basic file reading.
//
//Implement functions textdump and hexdump that will read the given file (the file name in filename parameter) and print its contents to the screen. Both functions return the number of bytes read, or -1 if there was error in opening the file. You will need to implement two output formats as follows:
//
//In Exercise (a) the file is output as text characters. If the read character is printable (as determined by the isprint function call), it should be printed as is. If the character is not printable, '?' should be printed instead.
//
//In Exercise (b) the file content should be printed as hexdump. Each byte is printed as hexadecimal number that uses exactly two characters on the screen. If the hexadecimal number is less than 0x10, a leading zero is applied. Each hexadecimal number is followed by space. A line can have at most 16 hexadecimal numbers, after that a new line is started. Also the number at the end of the line should have a trailing space following it. Here is an example output: