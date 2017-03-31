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
void multiplicacion(BYTE a, BYTE b, BYTE *res);

int main(int argc, char const *argv[])
{
	BYTE a (0xf4);
	BYTE b (0x7d);
	BYTE c;
	multiplicacion(a,b,&c);
}
void multiplicacion(BYTE a, BYTE b, BYTE *res){
BYTE polinomio (0x1B);
BYTE *resultados=(BYTE*)malloc(sizeof(BYTE)*8);
resultados[0]=a; 
cout<<resultados[0].to_string()<<endl<<endl;
for (int i = 1; i < 7; i++)
{

	if(a[7]==1){//se desbordara
		a=((a<<1)^polinomio);
		resultados[i]=a;
	}
	else{
		a=(a<<1);
		resultados[i]=a;
	}
	cout<<resultados[i].to_string()<<endl<<endl;
}

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