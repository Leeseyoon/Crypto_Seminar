#ifndef _LEA_
#define _LEA_

void LEA_Enc(unsigned int* P, unsigned int* C, unsigned int* K);

void LEA_Enc_Round(unsigned int* X, unsigned int* X_out, unsigned int* RK);

int LEA_Enc_KeySch(unsigned int* K, unsigned int* RK);

void ctoi(unsigned char c[], unsigned int* i);


#endif 
