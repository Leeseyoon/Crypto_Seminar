#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lea.h"

#define KEY_SIZE	128 // 128, 192, 256

#define ROL(x, r) ((x << r) | (x >> (32-r)))
#define ROR(x, r) ((x >> r) | (x << (32-r)))
// #define blank 0xffffffff

// #define MODADD(x, y) ((x + y) & blank) // 안해도되는듯

#if KEY_SIZE == 128
char NB = 16;
char NK = 16;
char NR = 24;
char SIZE32 = 4;

#elif KEY_SIZE == 192
char NB = 16;
char NK = 24;
char NR = 28;
char SIZE32 = 6;

#elif KEY_SIZE == 256
char NB = 16;
char NK = 32;
char NR = 32;
char SIZE32 = 8;

#else
#endif

const unsigned int lamda[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 
							0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957 };



void LEA_Enc(unsigned int* P, unsigned int* C, unsigned int* K) // Nr = 24, 28, 32
{
	unsigned int* X = NULL;
	unsigned int* RK = NULL;

	X = (unsigned int*)malloc(NR);
	RK = (unsigned int*)malloc(144);
	int i = 0;

	LEA_Enc_KeySch(K, RK);
	for (i = 0; i < NR; i++)
	{
		//printf("%02x", P[i]);
		LEA_Enc_Round(&P[i], &C[i], &RK[i]);
	}
	printf("%02x", X[0]);
	memcpy(C, X, SIZE32); 
}

void LEA_Enc_Round(unsigned int* X, unsigned int* X_out, unsigned int* RK)
{
	unsigned int Temp = 0;

	Temp = X[0];
	X_out[0] = ROL(((X[0] | RK[0]) + (X[1] | RK[1])), 9);  //X_out[0] = ROL(MODADD((X[0] | RK[0]), X[1] | RK[1]), 9);
	X_out[1] = ROL(((X[1] | RK[2]) + (X[2] | RK[3])), 5);  //X_out[1] = ROL(MODADD((X[1] | RK[2]), X[2] | RK[3]), 5);
	X_out[2] = ROL(((X[2] | RK[4]) + (X[3] | RK[5])), 3);  //X_out[2] = ROL(MODADD((X[2] | RK[4]), X[3] | RK[5]), 3);
	X_out[3] = Temp;
}

int LEA_Enc_KeySch(unsigned int* K, unsigned int* RK)
{
	unsigned int T[4] = { 0x00, };

	int i = 0;
	int j = 0;
	int k = 0;
	int mod_i = 0;

	if (K == NULL)
		return -1;

	if (T == NULL)
		return -1;
	
	for (i = 0; i < 4; i++)
		T[i] = K[i];

	if (KEY_SIZE == 128)
	{
		for (i = 0; i < NR; i++)
		{
			mod_i = i % 4;

			T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
			T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 1))), 3);
			T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 2))), 6);
			T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 3))), 11);

			j = i * 6;

			RK[0 + j] = T[0];
			RK[1 + j] = T[1];
			RK[2 + j] = T[2];
			RK[3 + j] = T[1];
			RK[4 + j] = T[3];
			RK[5 + j] = T[1];
		}
		
		return 0;
	}
	else if (KEY_SIZE == 192)
	{
		for (i = 0; i < NR; i++)
		{
			mod_i = i % 6;

			T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
			T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 1))), 3);
			T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 2))), 6);
			T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 3))), 11);
			T[4] = ROL((T[4] + ROL(lamda[mod_i], (i + 4))), 13);
			T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 5))), 17);

			j = i * 6;

			RK[0 + j] = T[0];
			RK[1 + j] = T[1];
			RK[2 + j] = T[2];
			RK[3 + j] = T[3];
			RK[4 + j] = T[4];
			RK[5 + j] = T[5];
		}
		return 0;
	}
	else
	{
		for (i = 0; i < NR; i++)
		{
			mod_i = i % 8;
			k = i % 4;
			j = i * 6;

			if (k == 0)
			{
				T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], i)), 3);
				T[2] = ROL((T[2] + ROL(lamda[mod_i], i)), 6);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], i)), 11);
				T[4] = ROL((T[4] + ROL(lamda[mod_i], i)), 13);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], i)), 17);

				RK[0 + j] = T[0];
				RK[1 + j] = T[1];
				RK[2 + j] = T[2];
				RK[3 + j] = T[3];
				RK[4 + j] = T[4];
				RK[5 + j] = T[5];
				
			}
			else if (k == 1)
			{
				T[6] = ROL((T[6] + ROL(lamda[mod_i], i)), 1);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], (i + 1))), 3);
				T[0] = ROL((T[0] + ROL(lamda[mod_i], (i + 2))), 6);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 3))), 11);
				T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 4))), 13);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 5))), 17);

				RK[0 + j] = T[6];
				RK[1 + j] = T[7];
				RK[2 + j] = T[0];
				RK[3 + j] = T[1];
				RK[4 + j] = T[2];
				RK[5 + j] = T[3];
				
			}
			else if (k == 2)
			{
				T[4] = ROL((T[4] + ROL(lamda[mod_i], i)), 1);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], i)), 3);
				T[6] = ROL((T[6] + ROL(lamda[mod_i], i)), 6);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], i)), 11);
				T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 13);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], i)), 17);

				RK[0 + j] = T[4];
				RK[1 + j] = T[5];
				RK[2 + j] = T[6];
				RK[3 + j] = T[7];
				RK[4 + j] = T[0];
				RK[5 + j] = T[1];
				
			}
			else
			{
				T[2] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
				T[3] = ROL((T[1] + ROL(lamda[mod_i], i)), 3);
				T[4] = ROL((T[2] + ROL(lamda[mod_i], i)), 6);
				T[5] = ROL((T[3] + ROL(lamda[mod_i], i)), 11);
				T[6] = ROL((T[4] + ROL(lamda[mod_i], i)), 13);
				T[7] = ROL((T[5] + ROL(lamda[mod_i], i)), 17);

				RK[0 + j] = T[2];
				RK[1 + j] = T[3];
				RK[2 + j] = T[4];
				RK[3 + j] = T[5];
				RK[4 + j] = T[6];
				RK[5 + j] = T[7];
			}
		}
		return 0;
	}

}

void ctoi(unsigned char c[], unsigned int* i) // padding함수 -> ctoi 함수 ( 이 순서로 돌아가야할듯)
{
	int count = 0;
	int size = 0;

	for (count = 0; count < 4; count++)
	{
		size = count * 4;
		i[count] = (int)(c[size]) | ((int)(c[size + 1]) << 8) | ((int)(c[size + 2]) << 16) | ((int)(c[size + 3]) << 24);
	}
	
}
