#include <iostream>
#include <bitset>
#include "AESclass.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
	AESclass aes;
	BYTE *vent=(BYTE*)malloc(sizeof(BYTE)*4);
	BYTE *vsal=(BYTE*)malloc(sizeof(BYTE)*4);
	vent[0]=BYTE (0xd4);
	vent[1]=BYTE (0xbf);
	vent[2]=BYTE (0x5d);
	vent[3]=BYTE (0x30);
	aes.multVector(vent, vsal);	
	for (int i = 0; i < 4; i++)
	{
		cout<<vsal[i]<<endl;
	}
	return 0;
}