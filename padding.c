#include "padding.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


void ISO_IEC_7816_4(unsigned char* P, unsigned char* PAD, int size)
{

	//int size = 0;
	int pad_size = 0;
	int i = 0;
	
	//size = sizeof(P);
	i = size & 15;
	if (i == 0)
	{
		pad_size = size + 16;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		PAD[size] = 0x80;
		
	}
	else
	{
		i = 16 - i;
		pad_size = size + i;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		PAD[size] = 0x80;

	}
}

void ANSI_X_9_23(unsigned char* P, unsigned char* PAD)
{
	int size = 0;
	int pad_size = 0;
	int i = 0;
	size = sizeof(P);
	i = size & 15;
	if (i == 0)
	{
		pad_size = size + 16;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		PAD[pad_size - 1] = 16;
	}
	else
	{
		i = 16 - i;
		pad_size = size + i;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		PAD[pad_size - 1] = 16 - i;

	}
}

void PKCS_7(unsigned char* P, unsigned char* PAD)
{
	int size = 0;
	int pad_size = 0;
	int i = 0;
	int j = 0;
	size = sizeof(P);
	i = size & 15;
	if (i == 0)
	{
		pad_size = size + 16;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		for (j = size; j < pad_size; j++)
			PAD[j] = 16;
	}
	else
	{
		i = 16 - i;
		pad_size = size + i;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		i = 16 - i;
		for (j = size; j < pad_size; j++)
			PAD[j] = i;
	}
}

void ISO_10126(unsigned char* P, unsigned char* PAD)
{
	int size = 0;
	int pad_size = 0;
	int i = 0;
	int j = 0;
	size = sizeof(P);
	i = size & 15;
	if (i == 0)
	{
		pad_size = size + 16;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		for (j = size; j < pad_size; j++)
			PAD[j] = 16;
	}
	else
	{
		i = 16 - i;
		pad_size = size + i;

		PAD = (unsigned char*)calloc(pad_size, sizeof(unsigned char));
		memcpy(PAD, P, size);
		i = 16 - i;
		for (j = size; j < pad_size; j++)
			PAD[j] = i;
	}
}
