#include <iostream>
#include <bitset>
using namespace std;

typedef bitset<8> BYTE;
void BintoDec(BYTE a,uint *b);
void BintoHex(BYTE a,std::string  *b);
void HexToBin(std::string  a,BYTE *b);
void HexToDec(uint a,uint *b);
void DecToBin(uint a,BYTE *b);
void DecToHex(uint a,uint *b);
uint potencia(uint n,uint pot);
BYTE multiplicacion(BYTE a, BYTE b);
void MixColumns(BYTE *vecEnt, BYTE *VecSal);

int main(int argc, char const *argv[])
{
	//BYTE a (atoi(argv[1]));
	//BYTE b (atoi(argv[2]));
	//BYTE c;
	//multiplicacion(a,b,&c);
	BYTE *vent=(BYTE*)malloc(sizeof(BYTE)*4);
	BYTE *vsal=(BYTE*)malloc(sizeof(BYTE)*4);
	vent[0]=BYTE (0xd4);
	vent[1]=BYTE (0xbf);
	vent[2]=BYTE (0x5d);
	vent[3]=BYTE (0x30);
	MixColumns(vent, vsal);	
	for (int i = 0; i < 4; i++)
	{
		cout<<vsal[i]<<endl;
	}
//| d4 e0 b8 1e ┃       ┃ 02 03 01 01 ┃       ┃ 04 e0 48 28 ┃ 
//┃ bf b4 41 27 ┃       ┃ 01 02 03 01 ┃       ┃ 66 cb f8 06 ┃ 
//┃ 5d 52 11 98 ┃       ┃ 01 01 02 03 ┃       ┃ 81 19 d3 26 ┃ 
//┃ 30 ae f1 e5 ┃       ┃ 03 01 01 02 ┃       ┃ e5 9a 7a 4c ┃
}
BYTE multiplicacion(BYTE a, BYTE b){
	BYTE polinomio (0x1B);
	BYTE *resultados=(BYTE*)malloc(sizeof(BYTE)*8);
	BYTE *suma=(BYTE*)malloc(sizeof(BYTE)*8);

	//cout<<resultados[0].to_string()<<endl<<endl;
	for (int i = 0; i < 7; i++)
	{
		if(i!=0){
			if(a[7]==1){//se desbordara
					a=((a<<1)^polinomio);
					resultados[i]=a;
			}
			else{
				a=(a<<1);
				resultados[i]=a;
			}
		}
		else
		resultados[0]=a; 
		//cout<<resultados[i].to_string()<<endl<<endl;
		if(b[i]==1)
			suma[i]=bitset<8> (0xFF);
		else
			suma[i] =bitset<8> (0x00);
	}
	BYTE res=bitset<8> (0x00);
	res=((resultados[0]&suma[0] )^(resultados[1]&suma[1] )^(resultados[2]&suma[2] )^(resultados[3]&suma[3] )^(resultados[4]&suma[4] )^(resultados[5]&suma[5] )^(resultados[6]&suma[6])^(resultados[7]&suma[7]));
	//cout<<"Resultado: "<< *res<<endl;
	return res;
}
void MixColumns(BYTE *vecEnt, BYTE *VecSal){
	VecSal[0]=((multiplicacion(vecEnt[0],BYTE (0x02)))^(multiplicacion(vecEnt[1],BYTE (0x03)))^(vecEnt[2])^(vecEnt[3]));
	VecSal[1]=((multiplicacion(vecEnt[1],BYTE (0x02)))^(multiplicacion(vecEnt[2],BYTE (0x03)))^(vecEnt[0])^(vecEnt[3]));
	VecSal[2]=((multiplicacion(vecEnt[2],BYTE (0x02)))^(multiplicacion(vecEnt[3],BYTE (0x03)))^(vecEnt[0])^(vecEnt[1]));
	VecSal[3]=((multiplicacion(vecEnt[3],BYTE (0x02)))^(multiplicacion(vecEnt[0],BYTE (0x03)))^(vecEnt[1])^(vecEnt[2]));
}
void BintoDec(BYTE a,uint *b)
{
	*b=(uint)a.to_ulong();
}
void BintoHex(BYTE a,uint *b){

}

void HexToDec(uint a,uint *b){

}
void DecToBin(uint a,BYTE *b){
	int cont=0;
	while(a>0){
		b->set(cont,(a%2));
		a=(uint)a/2;
		cont++;
	}
}
void DecToHex(uint a,uint *b){

}
uint potencia(uint n,uint pot){
	uint aux=n;
	for (uint i = 1; i < pot; ++i)
	{
		n=n*aux;
	}
}
