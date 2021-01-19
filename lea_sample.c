#include "lea.h"

const unsigned int Delta[8] = {
		0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec,
		0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957
};


void ctoi(unsigned char *c, unsigned int *d) {



	for (int i = 0; i < 4; i++)
	{
		d[i] = (int)(c[(4 * i) + 3] << 24) | (int)(c[(4 * i) + 2] << 16) | (int)(c[(4 * i) + 1] << 8) | (int)(c[(4 * i)]);
	}


}


int L_ROL(unsigned int a, unsigned int num) {

	a = ((a << num) | (a >> (32 - num)));
	return a;

}

int R_ROL(unsigned int a, unsigned int num) {

	a = ((a >> num) | (a << (32 - num)));
	return a;

}

void E_Keyschedule(unsigned char *Key, unsigned int *RoundKey)
{

	unsigned int T[4] = { 0, };
	ctoi(Key, T);


	for (int i = 0; i < 24; i++)
	{
		T[0] = L_ROL((T[0] + L_ROL(Delta[i % 4], i)), 1);
		T[1] = L_ROL((T[1] + L_ROL(Delta[i % 4], i + 1)), 3);
		T[2] = L_ROL((T[2] + L_ROL(Delta[i % 4], i + 2)), 6);
		T[3] = L_ROL((T[3] + L_ROL(Delta[i % 4], i + 3)), 11);

		RoundKey[6 * i] = T[0];
		RoundKey[6 * i + 1] = T[1];
		RoundKey[6 * i + 2] = T[2];
		RoundKey[6 * i + 3] = T[1];
		RoundKey[6 * i + 4] = T[3];
		RoundKey[6 * i + 5] = T[1];
	}
}

void Enc_round(unsigned int *Roundkey, unsigned char *P, unsigned char *C)
{
	unsigned int X[4] = { 0, };
	unsigned int Temp = 0;

	ctoi(P, X);


	for (int i = 0; i < 24; i++)
	{
		Temp = X[0];
		X[0] = L_ROL((X[0] ^ Roundkey[6 * i]) + (X[1] ^ Roundkey[(6 * i) + 1]), 9);
		X[1] = R_ROL((X[1] ^ Roundkey[(6 * i) + 2]) + (X[2] ^ Roundkey[(6 * i) + 3]), 5);
		X[2] = R_ROL((X[2] ^ Roundkey[(6 * i) + 4]) + (X[3] ^ Roundkey[(6 * i) + 5]), 3);
		X[3] = Temp;//일단 이거 아니지만

	}

	memcpy(C, X, 16);

}

void D_Keyschedule(unsigned char *Key, unsigned int *RoundKey) //키 스케줄 함수 선언 128비트에서
{
	unsigned int T[4] = { 0, };
	int j = 0;
	ctoi(Key, T);
	for (int i = 0; i < 24; i++)
	{
		T[0] = L_ROL(T[0] + L_ROL(Delta[i % 4], i), 1);
		T[1] = L_ROL(T[1] + L_ROL(Delta[i % 4], i + 1), 3);
		T[2] = L_ROL(T[2] + L_ROL(Delta[i % 4], i + 2), 6);
		T[3] = L_ROL(T[3] + L_ROL(Delta[i % 4], i + 3), 11);

		RoundKey[6 * (23 - i)] = T[0];
		RoundKey[6 * (23 - i) + 1] = T[1];
		RoundKey[6 * (23 - i) + 2] = T[2];
		RoundKey[6 * (23 - i) + 3] = T[1];
		RoundKey[6 * (23 - i) + 4] = T[3];
		RoundKey[6 * (23 - i) + 5] = T[1];
	}

}

void Dec_round(unsigned int *Roundkey, unsigned char *C, unsigned char *D)
{
	unsigned int X[4] = { 0, };
	unsigned int Temp3, Temp2, Temp1 = 0;

	ctoi(C, X);


	for (int i = 0; i < 24; i++)
	{
		Temp3 = X[3];
		Temp2 = X[2];
		Temp1 = X[1];
		X[1] = ((R_ROL(X[0], 9)) - (Temp3 ^ (Roundkey[6 * i]))) ^ Roundkey[6 * i + 1];
		X[2] = ((L_ROL(Temp1, 5)) - (X[1] ^ (Roundkey[6 * i + 2]))) ^ Roundkey[6 * i + 3];
		X[3] = ((L_ROL(Temp2, 3)) - (X[2] ^ (Roundkey[6 * i + 4]))) ^ Roundkey[6 * i + 5];
		X[0] = Temp3;
		//printf("%08x %08x %08x %08x \n", X[0], X[1], X[2], X[3]);
	}
	memcpy(D, X, 16);


}


void LEA_ENC(unsigned char *Key, unsigned char *P, unsigned char *C)
{
	unsigned int Roundkey[144] = { 0, };


	E_Keyschedule(&Key[0], &Roundkey[0]); //Keyschedule(K, Roundkey);
	Enc_round(&Roundkey[0], &P[0], &C[0]);
}

void LEA_DEC(unsigned char *Key, unsigned char *C, unsigned char *D)
{
	unsigned int dRoundkey[144] = { 0, };

	D_Keyschedule(Key, dRoundkey);
	Dec_round(dRoundkey, C, D);
}
