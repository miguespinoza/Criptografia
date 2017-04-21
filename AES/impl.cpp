#include <iostream>
#include <bitset>
#include "AESclass.cpp"
using namespace std;

void printMatrix(BYTE **mat);
int main(int argc, char const *argv[])
{
	AESclass aes;
	BYTE *vent=(BYTE*)malloc(sizeof(BYTE)*4);
	BYTE *vsal=(BYTE*)malloc(sizeof(BYTE)*4);
	vent[0]=BYTE (0x00);
	vent[1]=BYTE (0x00);
	vent[2]=BYTE (0x00);
	vent[3]=BYTE (0x0);
	BYTE **mEnt=(BYTE**)malloc(sizeof(BYTE)*4);
	BYTE **mSal=(BYTE**)malloc(sizeof(BYTE)*4);
	BYTE **rKey=(BYTE**)malloc(sizeof(BYTE)*4);
	for (int i = 0; i < 4; ++i)
	{
		mEnt[i]=(BYTE*)malloc(sizeof(BYTE)*4);
		mSal[i]=(BYTE*)malloc(sizeof(BYTE)*4);
		rKey[i]=(BYTE*)malloc(sizeof(BYTE)*4);
	}
	mEnt[0][0]= BYTE(0xba);
	mEnt[0][1]= BYTE(0x75);
	mEnt[0][2]= BYTE(0xf4);
	mEnt[0][3]= BYTE(0x7a);
	mEnt[1][0]= BYTE(0x84);
	mEnt[1][1]= BYTE(0xa4);
	mEnt[1][2]= BYTE(0x8d);
	mEnt[1][3]= BYTE(0x32);
	mEnt[2][0]= BYTE(0xe8);
	mEnt[2][1]= BYTE(0x8d);
	mEnt[2][2]= BYTE(0x06);
	mEnt[2][3]= BYTE(0x0e);
	mEnt[3][0]= BYTE(0x1b);
	mEnt[3][1]= BYTE(0x40);
	mEnt[3][2]= BYTE(0x7d);
	mEnt[3][3]= BYTE(0x5d);

	rKey[0][0]= BYTE(0xe2);
	rKey[0][1]= BYTE(0x32);
	rKey[0][2]= BYTE(0xfc);
	rKey[0][3]= BYTE(0xf1);
	rKey[1][0]= BYTE(0x91);
	rKey[1][1]= BYTE(0x12);
	rKey[1][2]= BYTE(0x91);
	rKey[1][3]= BYTE(0x88);
	rKey[2][0]= BYTE(0xb1);
	rKey[2][1]= BYTE(0x59);
	rKey[2][2]= BYTE(0xe4);
	rKey[2][3]= BYTE(0xe6);
	rKey[3][0]= BYTE(0xd6);
	rKey[3][1]= BYTE(0x79);
	rKey[3][2]= BYTE(0xa2);
	rKey[3][3]= BYTE(0x93);


	aes.addRoundKey(mEnt,mSal,rKey);
	printMatrix(mSal);
	mEnt=mSal;
	aes.subByte(mEnt,mSal);
	cout<<endl;
	printMatrix(mSal);
	return 0;
}

void printMatrix(BYTE **mat){
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout<<hex<<mat[j][i].to_ulong()<<"   ";
		}
		cout<<endl;
	}
}

