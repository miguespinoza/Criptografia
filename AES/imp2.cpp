#include <iostream>
#include <cstring>
#include <bitset>
#include "AESclass.cpp"
using namespace std;

int	main(int argc, char const *argv[])
{
	AESclass aes;
		BYTE **rKey=(BYTE**)malloc(sizeof(BYTE)*4);
	for (int i = 0; i < 4; ++i)
	{
		rKey[i]=(BYTE*)malloc(sizeof(BYTE)*4);
	}
		rKey[0][0]= BYTE(0x2b);
	rKey[0][1]= BYTE(0x7e);
	rKey[0][2]= BYTE(0x15);
	rKey[0][3]= BYTE(0x16);
	rKey[1][0]= BYTE(0x28);
	rKey[1][1]= BYTE(0xae);
	rKey[1][2]= BYTE(0xd2);
	rKey[1][3]= BYTE(0xa6);
	rKey[2][0]= BYTE(0xab);
	rKey[2][1]= BYTE(0xf7);
	rKey[2][2]= BYTE(0x15);
	rKey[2][3]= BYTE(0x88);
	rKey[3][0]= BYTE(0x09);
	rKey[3][1]= BYTE(0xcf);
	rKey[3][2]= BYTE(0x4f);
	rKey[3][3]= BYTE(0x3c);
	//aes.encryptTEST();
	std::string entrada="Hola buenos dias senor juez";
	std::string sal=aes.encrypt(entrada,rKey);
	cout<<sal;
	return 0;
}