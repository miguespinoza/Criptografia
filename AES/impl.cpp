#include <iostream>
#include <cstring>
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
	/*mEnt[0][0]= BYTE(0xba);
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
	mEnt[3][3]= BYTE(0x5d);*/

	mEnt[0][0]= BYTE(0x32);
	mEnt[0][1]= BYTE(0x43);
	mEnt[0][2]= BYTE(0xf6);
	mEnt[0][3]= BYTE(0xa8);
	mEnt[1][0]= BYTE(0x88);
	mEnt[1][1]= BYTE(0x5a);
	mEnt[1][2]= BYTE(0x30);
	mEnt[1][3]= BYTE(0x8d);
	mEnt[2][0]= BYTE(0x31);
	mEnt[2][1]= BYTE(0x31);
	mEnt[2][2]= BYTE(0x98);
	mEnt[2][3]= BYTE(0xa2);
	mEnt[3][0]= BYTE(0xe0);
	mEnt[3][1]= BYTE(0x37);
	mEnt[3][2]= BYTE(0x07);
	mEnt[3][3]= BYTE(0x34);

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

	printMatrix(mEnt);
	aes.addRoundKey(mEnt,rKey);
	//aes.setKey(mEnt);
	printMatrix(mEnt);
	printf("subByte\n");
	aes.subByte(mEnt);
	printMatrix(mEnt);
	printf("shiftRows\n");
	aes.shiftRows(mEnt);
	printMatrix(mEnt);
	printf("mixColumns\n");
	aes.mixColums(mEnt);
	printMatrix(mEnt);
	/*aes.exchangeMatrix(mEnt,mSal);
	aes.subByte(mEnt,mSal);
	cout<<endl;
	printMatrix(mSal);
	//mEnt=mSal;
	aes.exchangeMatrix(mEnt,mSal);
	
	aes.shiftRows(mEnt,mSal);
	cout<<endl;
	printMatrix(mSal);*/
	return 0;
}

void printMatrix(BYTE **mat){
	for (int fila = 0; fila < 4; fila++)
	{
		for (int col = 0; col < 4; ++col)
		{
			cout<<hex<<mat[col][fila].to_ulong()<<"   ";
		}
		cout<<endl;
	}
}

