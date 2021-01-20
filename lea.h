#ifndef _LEA_
#define _LEA_

void LEA_Enc(unsigned int* P, unsigned int* C, unsigned int* K);

void LEA_Enc_Round(unsigned int* X, unsigned int* RK);

int LEA_Enc_KeySch(unsigned int* K, unsigned int* RK);

void LEA_Dec(unsigned int* C, unsigned int* P, unsigned int* K);

void LEA_Dec_Round(unsigned int* X, unsigned int* RK);

int LEA_Dec_KeySch(unsigned int* K, unsigned int* RK);

void ctoi(unsigned char c[], unsigned int* i);

void ctoi_key(unsigned char c[], unsigned int* i);

#endif 
