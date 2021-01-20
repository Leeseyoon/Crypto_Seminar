#ifndef _PADDING_
#define _PADDING_

void ISO_IEC_7816_4(unsigned char* P, unsigned char* PAD, int size);

void ANSI_X_9_23(unsigned char* P, unsigned char* PAD);

void PKCS_7(unsigned char* P, unsigned char* PAD);

void ISO_10126(unsigned char* P, unsigned char* PAD);

#endif 
