#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lea.h"

void main()
{
	unsigned char Test_Key_128[16] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0 };
	unsigned char Test_PT_128[16] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	unsigned char Test_CT_128[16] = { 0x9f, 0xc8, 0x4e, 0x35, 0x28, 0xc6, 0xc6, 0x18, 0x55, 0x32, 0xc7, 0xa7, 0x04, 0x64, 0x8b, 0xfd };

	unsigned int* Test_Key = NULL;
	unsigned int* Test_PT = NULL;
	unsigned int* Test_CT = NULL;
	unsigned int* RK = (unsigned int*)malloc(144);

	int i = 0;
	int size = 0;
	
	size = sizeof(Test_Key_128) >> 2;
	Test_Key = (unsigned int*)malloc(16); // 128 -> 16 --> int 4 개 필요
	memset(Test_Key, 0x00, 16);
	Test_PT = (unsigned int*)malloc(16);
	Test_CT = (unsigned int*)malloc(16); // 블록 길이는 항상 16이고 CT 길이 == PT 길이

	ctoi(Test_Key_128, Test_Key);
	ctoi(Test_PT_128, Test_PT);
	ctoi(Test_CT_128, Test_CT);
	
	LEA_Enc(Test_PT, Test_CT, Test_Key);
	
	

}
