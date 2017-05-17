#include <iostream>
#include <cstring>
#include <bitset>
#include "AESclass.cpp"
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
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
	BYTE *sal=(BYTE*)malloc(sizeof(BYTE)*16);
	BYTE *ent=(BYTE*)malloc(sizeof(BYTE)*16);
	if (argc<2)
	{
		exit(-1);
	}
	std::ifstream ifs (argv[1], ios::binary);
	std::ofstream ofs (argv[2], ios::binary);
	char *letra=(char*)malloc(1);
	char s;
	uint c = ifs.get();
	uint cont=0;
  	while (ifs.good()) {
  		cont++;
    	//std::cout << hex<<c;
    	c = ifs.get();
    	if (cont==16)
    	{
    		aes.encrypt(ent,rKey,sal);
    		for (int i = 0; i < 16; ++i)
    		{
    			
    			s=(char)sal[i].to_ulong();
    			ofs.write(&s,1);
    		}
    		cont=0;
    	}
  	}
  	if (cont>0)
  	{
  		for (int i = cont; i < 15; ++i)
  		{
  			ent[i+1]=BYTE(0x00);
  		}
  		aes.encrypt(ent,rKey,sal);
		for (int i = 0; i < 16; ++i)
		{
			   s=(char)sal[i].to_ulong();
    			ofs.write(&s,1);
		}
		cont=0;
  	}
  	ofs.close();
  	ifs.close();
	return 0;
}