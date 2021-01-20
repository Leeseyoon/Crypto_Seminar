#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lea.h"
#include "padding.h"

void main()
{
	unsigned char Test_Key_128[16] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0 };
	unsigned char Test_PT_128[16] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	unsigned char Test_CT_128[16] = { 0x9f, 0xc8, 0x4e, 0x35, 0x28, 0xc6, 0xc6, 0x18, 0x55, 0x32, 0xc7, 0xa7, 0x04, 0x64, 0x8b, 0xfd };

	unsigned char Test_Key_192[24] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0 
										, 0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87 };
	unsigned char Test_PT_192[16] = { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f };
	unsigned char Test_CT_192[16] = { 0x6f, 0xb9, 0x5e, 0x32, 0x5a, 0xad, 0x1b, 0x87, 0x8c, 0xdc, 0xf5, 0x35, 0x76, 0x74, 0xc6, 0xf2 };

	unsigned char Test_Key_256[32] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0
										, 0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x1e, 0x0f };
	unsigned char Test_PT_256[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f };
	unsigned char Test_CT_256[16] = { 0xd6, 0x51, 0xaf, 0xf6, 0x47, 0xb1, 0x89, 0xc1, 0x3a, 0x80, 0x00, 0xca, 0x27, 0xf9, 0xe1, 0x97 };

	unsigned char Test_PT_Padding[10] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19 };

	unsigned char* padding = NULL;

	unsigned int* Test_Key = NULL;
	unsigned int* Test_PT = NULL;
	unsigned int* Test_CT = NULL;
	unsigned int* Test = NULL;
	unsigned int* Test_D = NULL; 

	int i = 0;
	int size = 0;


	//Test_Key = (unsigned int*)malloc(16); // 128 -> 16 --> int 4 개 필
	//Test_PT = (unsigned int*)malloc(16);
	//Test = (unsigned int*)malloc(16);
	//Test_D = (unsigned int*)malloc(16);
	//Test_CT = (unsigned int*)malloc(16); // 블록 길이는 항상 16이고 CT 길이 == PT 길이

	//ctoi(Test_Key_128, Test_Key);
	//ctoi(Test_PT_128, Test_PT);
	//ctoi(Test_CT_128, Test_CT);

	//Test_Key = (unsigned int*)malloc(24); // 128 -> 16 --> int 4 개 필요
	//Test_PT = (unsigned int*)malloc(16);
	//Test = (unsigned int*)malloc(16);
	//Test_D = (unsigned int*)malloc(16);
	//Test_CT = (unsigned int*)malloc(16); // 블록 길이는 항상 16이고 CT 길이 == PT 길이

	//ctoi(Test_Key_192, Test_Key);
	//ctoi(Test_PT_192, Test_PT);
	//ctoi(Test_CT_192, Test_CT);

	//Test_Key = (unsigned int*)malloc(32); // 128 -> 16 --> int 4 개 필요
	//Test_PT = (unsigned int*)malloc(16);
	//Test = (unsigned int*)malloc(16);
	//Test_D = (unsigned int*)malloc(16);
	//Test_CT = (unsigned int*)malloc(16); // 블록 길이는 항상 16이고 CT 길이 == PT 길이

	//ctoi_key(Test_Key_256, Test_Key);
	//ctoi(Test_PT_256, Test_PT);
	//ctoi(Test_CT_256, Test_CT);

	//LEA_Enc(Test_PT, Test, Test_Key); // 암호화 128 테스트 벡터까지는 맞음

	//LEA_Dec(Test, Test_D, Test_Key); // 암호화 128 테스트 벡터까지는 맞음

	//printf("%02x", Test_D[0]);

	i = sizeof(Test_PT_128);

	ISO_IEC_7816_4(Test_PT_128, padding, i);

	i = sizeof(Test_PT_Padding);

	ISO_IEC_7816_4(Test_PT_Padding, padding, i);

	i = sizeof(Test_PT_128);

	ANSI_X_9_23(Test_PT_128, padding, i);

	i = sizeof(Test_PT_Padding);

	ANSI_X_9_23(Test_PT_Padding, padding, i);

	i = sizeof(Test_PT_128);

	PKCS_7(Test_PT_128, padding, i);

	i = sizeof(Test_PT_Padding);

	PKCS_7(Test_PT_Padding, padding, i);

	i = sizeof(Test_PT_128);

	ISO_10126(Test_PT_128, padding, i);

	i = sizeof(Test_PT_Padding);

	ISO_10126(Test_PT_Padding, padding, i);

}
