#include <iostream>
#include <cstring>
#include <bitset>
#include "AESclass.cpp"
#include <fstream>
using namespace std;
void CBC( BYTE **rKey, char const *archEnt, char const *archSal );
void CFB( BYTE **rKey, char const *archEnt, char const *archSal );

int main(int argc, char const *argv[])
{
	
	BYTE **rKey=(BYTE**)malloc(sizeof(BYTE)*4);
	//BYTE initVec[16]={BYTE(0x12),BYTE(0x22),BYTE(0x122),BYTE(0x42),BYTE(0x13),BYTE(0x112),BYTE(0x222),BYTE(0x92),BYTE(0x11),BYTE(0x15),BYTE(0x31),BYTE(34),BYTE(0x54),BYTE(0x129),BYTE(0x128)};
	BYTE *initVec=(BYTE *)malloc(sizeof(BYTE)*16);
	BYTE *sal=(BYTE*)malloc(sizeof(BYTE)*16);
	BYTE *ent=(BYTE*)malloc(sizeof(BYTE)*16);
	for (int i = 0; i < 16; ++i)
	{
		initVec[i]=BYTE(i);
	}
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
	if (argc<2)
	{
		exit(-1);
	}
	CBC(rKey,argv[1],argv[2]);
	//CFB(rKey,argv[1],argv[2]);
  	
	return 0;
}

void CBC( BYTE **rKey, char const *archEnt, char const *archSal ){
	AESclass aes;
	std::ifstream ifs (archEnt, std::ios::binary);
	std::ofstream ofs (archSal, ios::out | ios::binary);
	BYTE *sal=(BYTE*)malloc(sizeof(BYTE)*16);
	BYTE *ent=(BYTE*)malloc(sizeof(BYTE)*16);
	char s;
	
	uint c;
	int cont=0;;
	//while (ifs.good()) {
	while (ifs.good()) {
  		cont++;
  		c=ifs.get();
  		if(c==0xffffffff)
  			break;
  		cout<<hex<<c<<endl;
    	ent[cont]=BYTE(c);
    	if (cont==16)
    	{
    		aes.encrypt(ent,rKey,sal);
    		for (int i = 0; i < 16; ++i)
    		{
    			//cout<<hex<<n<<endl;
    			s=(char)sal[i].to_ulong();
    			cout<<hex<<sal[i].to_ulong()<<endl;
    			ofs.write( &s, 1) ;
    		}
    		cont=0;
    		memset(ent, 0, 16);
    	}
  	}
  	if (cont>0)
  	{
  		for (int i = cont; i < 16; ++i)
  		{
  			ent[i]=BYTE(0);
  		}
		aes.encrypt(ent,rKey,sal);
		for (int i = 0; i < 16; ++i)
		{
			s=(char)sal[i].to_ulong();
    		ofs.write( &s, 1) ;
		}
		cont=0;
		memset(ent, 0, 16);
  	}
  	ifs.close();
  	ofs.close();
}
void CFB( BYTE **rKey, char const *archEnt, char const *archSal ){
	AESclass aes;
	std::ifstream ifs (archEnt, std::ios::binary);
	std::ofstream ofs (archSal, ios::binary);
	BYTE *sal=(BYTE*)malloc(sizeof(BYTE)*16);
	BYTE *ent=(BYTE*)malloc(sizeof(BYTE)*16);
	char s;
	unsigned long n;
	uint c;
	int cont=0;
	for (int i = 0; i < 16; ++i)//vector aleatorio
	{
		sal[i]=BYTE(i);
	}
	while (ifs.good()) {
  		cont++;
    	if(c==0xffffffff)
  			break;
    	c=ifs.get();
    	ent[cont]=BYTE(c);
    	if (cont==16)
    	{
    		aes.encrypt(sal,rKey,sal);
    		for (int i = 0; i < 16; ++i)
    		{
    			sal[i]=ent[i]^sal[i];
    		}
    		for (int i = 0; i < 16; ++i)
			{
				s=(char)sal[i].to_ulong();
				cout<<hex<<sal[i].to_ulong()<<endl;
	    		ofs.write( &s, 1) ;
			}
    		cont=0;
    		memset(ent, 0, 16);
    	}

  	}
  	if (cont>0)
  	{
		aes.encrypt(sal,rKey,sal);
		for (int i = 0; i < 16; ++i)
		{
			sal[i]=ent[i]^sal[i];
		}
		for (int i = 0; i < 16; ++i)
		{
			s=(char)sal[i].to_ulong();
    		ofs.write( &s, 1) ;
		}
		cont=0;
    	memset(ent, 0, 16);
  	}
}