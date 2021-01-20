#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lea.h"

#define KEY_SIZE	192 // 128, 192, 256

#define ROL(x, r) ((x << r) | (x >> (32-r)))
#define ROR(x, r) ((x >> r) | (x << (32-r)))
// #define blank 0xffffffff

// #define MODADD(x, y) ((x + y) & blank) // 안해도되는듯

#if KEY_SIZE == 128
char NB = 16;
#define NK = 16
char NR = 24;
#define SIZE32 4
#define MEM 576

#elif KEY_SIZE == 192
char NB = 16;
#define NK = 24
char NR = 28;
//char SIZE32 = 6;
#define SIZE32 6
#define MEM 672

#elif KEY_SIZE == 256
char NB = 16;
#define NK = 32
char NR = 32;
#define SIZE32 8
#define MEM 768

#else
#endif

const unsigned int lamda[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec,
							0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957 };



void LEA_Enc(unsigned int* P, unsigned int* C, unsigned int* K) // Nr = 24, 28, 32
{
	int i = 0;
	unsigned int* RK = NULL;
	unsigned int* Temp = NULL;

	Temp = (unsigned int*)malloc(16);
	memcpy(Temp, P, 16);

	RK = (unsigned int*)malloc(MEM); //128 : 576 / 192 : 672 

	LEA_Enc_KeySch(K, RK);
	for (i = 0; i < NR; i++)
	{	
		LEA_Enc_Round(Temp, &RK[i * 6]);
	}
	free(RK);
	memcpy(C, Temp, 16);
	free(Temp);
}

void LEA_Enc_Round(unsigned int* X, unsigned int* RK)
{
	unsigned int Temp = 0;

	Temp = X[0];
	X[0] = ROL(((X[0] ^ RK[0]) + (X[1] ^ RK[1])), 9);  //X_out[0] = ROL(MODADD((X[0] | RK[0]), X[1] | RK[1]), 9);
	X[1] = ROR(((X[1] ^ RK[2]) + (X[2] ^ RK[3])), 5);  //X_out[1] = ROL(MODADD((X[1] | RK[2]), X[2] | RK[3]), 5);
	X[2] = ROR(((X[2] ^ RK[4]) + (X[3] ^ RK[5])), 3);  //X_out[2] = ROL(MODADD((X[2] | RK[4]), X[3] | RK[5]), 3);
	X[3] = Temp;
}

int LEA_Enc_KeySch(unsigned int* K, unsigned int* RK)
{
	unsigned int T[SIZE32] = { 0x00, }; //192
	int i = 0;
	int j = 0;
	int k = 0;
	int mod_i = 0;

	if (K == NULL)
		return -1;

	if (T == NULL)
		return -1;

	for (i = 0; i < SIZE32; i++)  // 128 : 4, 192 : 6, 8
		T[i] = K[i];

	if (KEY_SIZE == 128)
	{
		for (i = 0; i < NR; i++)
		{
			mod_i = i & 3; // % 4

			T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
			T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 1))), 3);
			T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 2))), 6);
			T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 3))), 11);

			j = (i << 2) + (i << 1); //i * 6;

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

			j = (i << 2) + (i << 1); //i * 6;

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
			mod_i = i & 7; // % 8
			k = i & 3; // % 4
			j = (i << 2) + (i << 1);//i * 6;

			if (k == 0)
			{
				T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 1))), 3);
				T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 2))), 6);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 3))), 11);
				T[4] = ROL((T[4] + ROL(lamda[mod_i], (i + 4))), 13);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 5))), 17);

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
				T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 1))), 3);
				T[6] = ROL((T[6] + ROL(lamda[mod_i], (i + 2))), 6);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], (i + 3))), 11);
				T[0] = ROL((T[0] + ROL(lamda[mod_i], (i + 4))), 13);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 5))), 17);

				RK[0 + j] = T[4];
				RK[1 + j] = T[5];
				RK[2 + j] = T[6];
				RK[3 + j] = T[7];
				RK[4 + j] = T[0];
				RK[5 + j] = T[1];

			}
			else
			{
				T[2] = ROL((T[2] + ROL(lamda[mod_i], i)), 1);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 1))), 3);
				T[4] = ROL((T[4] + ROL(lamda[mod_i], (i + 2))), 6);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 3))), 11);
				T[6] = ROL((T[6] + ROL(lamda[mod_i], (i + 4))), 13);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], (i + 5))), 17);

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

void LEA_Dec(unsigned int* C, unsigned int* P, unsigned int* K) // Nr = 24, 28, 32
{
	int i = 0;
	unsigned int* RK = NULL;
	unsigned int* Temp = NULL;

	Temp = (unsigned int*)malloc(16);
	memcpy(Temp, C, 16);

	RK = (unsigned int*)malloc(MEM); //576

	LEA_Dec_KeySch(K, RK);
	for (i = 0; i < NR; i++)
	{
		LEA_Dec_Round(Temp, &RK[i * 6]);
	}
	free(RK);
	memcpy(P, Temp, 16);
	free(Temp);
	
}

void LEA_Dec_Round(unsigned int* X, unsigned int* RK)
{
	unsigned int Temp_0 = 0;
	unsigned int Temp_1 = 0;
	unsigned int Temp_2 = 0;

	Temp_0 = X[0];
	Temp_1 = X[1];
	Temp_2 = X[2];
	
	X[0] = X[3]; 
	X[1] = (ROR(Temp_0, 9) - (X[0] ^ RK[0])) ^ RK[1]; 
	X[2] = (ROL(Temp_1, 5) - (X[1] ^ RK[2])) ^ RK[3]; 
	X[3] = (ROL(Temp_2, 3) - (X[2] ^ RK[4])) ^ RK[5]; 
}

int LEA_Dec_KeySch(unsigned int* K, unsigned int* RK)
{
	//unsigned int T[4] = { 0x00, }; // 128
	unsigned int T[SIZE32] = { 0x00, };

	int i = 0;
	int j = 0;
	int k = 0;
	int mod_i = 0;

	if (K == NULL)
		return -1;

	if (T == NULL)
		return -1;

	for (i = 0; i < SIZE32; i++) // 128:4 / 192: 6
		T[i] = K[i];

	if (KEY_SIZE == 128)
	{
		for (i = 0; i < NR; i++)
		{
			mod_i = i & 3; // % 4

			T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
			T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 1))), 3);
			T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 2))), 6);
			T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 3))), 11);

			j = (i << 2) + (i << 1); //i * 6;

			RK[138 - j] = T[0];
			RK[139 - j] = T[1];
			RK[140 - j] = T[2];
			RK[141 - j] = T[1];
			RK[142 - j] = T[3];
			RK[143 - j] = T[1];
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

			j = (i << 2) + (i << 1); //i * 6;

			RK[162 - j] = T[0];
			RK[163 - j] = T[1];
			RK[164 - j] = T[2];
			RK[165 - j] = T[3];
			RK[166 - j] = T[4];
			RK[167 - j] = T[5];
		}
		return 0;
	}
	else
	{
		for (i = 0; i < NR; i++)
		{
			mod_i = i & 7; // % 8
			k = i & 3; // % 4
			j = (i << 2) + (i << 1); //i * 6;

			if (k == 0)
			{
				T[0] = ROL((T[0] + ROL(lamda[mod_i], i)), 1);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 1))), 3);
				T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 2))), 6);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 3))), 11);
				T[4] = ROL((T[4] + ROL(lamda[mod_i], (i + 4))), 13);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 5))), 17);

				RK[186 - j] = T[0];
				RK[187 - j] = T[1];
				RK[188 - j] = T[2];
				RK[189 - j] = T[3];
				RK[190 - j] = T[4];
				RK[191 - j] = T[5];

			}
			else if (k == 1)
			{
				T[6] = ROL((T[6] + ROL(lamda[mod_i], i)), 1);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], (i + 1))), 3);
				T[0] = ROL((T[0] + ROL(lamda[mod_i], (i + 2))), 6);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 3))), 11);
				T[2] = ROL((T[2] + ROL(lamda[mod_i], (i + 4))), 13);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 5))), 17);

				RK[186 - j] = T[6];
				RK[187 - j] = T[7];
				RK[188 - j] = T[0];
				RK[189 - j] = T[1];
				RK[190 - j] = T[2];
				RK[191 - j] = T[3];

			}
			else if (k == 2)
			{
				T[4] = ROL((T[4] + ROL(lamda[mod_i], i)), 1);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 1))), 3);
				T[6] = ROL((T[6] + ROL(lamda[mod_i], (i + 2))), 6);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], (i + 3))), 11);
				T[0] = ROL((T[0] + ROL(lamda[mod_i], (i + 4))), 13);
				T[1] = ROL((T[1] + ROL(lamda[mod_i], (i + 5))), 17);

				RK[186 - j] = T[4];
				RK[187 - j] = T[5];
				RK[188 - j] = T[6];
				RK[189 - j] = T[7];
				RK[190 - j] = T[0];
				RK[191 - j] = T[1];

			}
			else
			{
				T[2] = ROL((T[2] + ROL(lamda[mod_i], i)), 1);
				T[3] = ROL((T[3] + ROL(lamda[mod_i], (i + 1))), 3);
				T[4] = ROL((T[4] + ROL(lamda[mod_i], (i + 2))), 6);
				T[5] = ROL((T[5] + ROL(lamda[mod_i], (i + 3))), 11);
				T[6] = ROL((T[6] + ROL(lamda[mod_i], (i + 4))), 13);
				T[7] = ROL((T[7] + ROL(lamda[mod_i], (i + 5))), 17);

				RK[186 - j] = T[2];
				RK[187 - j] = T[3];
				RK[188 - j] = T[4];
				RK[189 - j] = T[5];
				RK[190 - j] = T[6];
				RK[191 - j] = T[7];
			}
		}
		return 0;
	}

}

void ctoi(unsigned char c[], unsigned int* i) // padding함수 -> ctoi 함수 ( 이 순서로 돌아가야할듯)
{
	int count = 0;
	int size = 0;

	for (count = 0; count < 4; count++) // 4 6 8
	{
		size = count * 4;
		i[count] = (int)(c[size]) | ((int)(c[size + 1]) << 8) | ((int)(c[size + 2]) << 16) | ((int)(c[size + 3]) << 24);
	}

}

void ctoi_key(unsigned char c[], unsigned int* i) // padding함수 -> ctoi 함수 ( 이 순서로 돌아가야할듯)
{
	int count = 0;
	int size = 0;

	for (count = 0; count < SIZE32; count++) // 4 6 8
	{
		size = count * 4;
		i[count] = (int)(c[size]) | ((int)(c[size + 1]) << 8) | ((int)(c[size + 2]) << 16) | ((int)(c[size + 3]) << 24);
	}

}
