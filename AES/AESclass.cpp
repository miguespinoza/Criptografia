#include <iostream>
#include <bitset>
using namespace std;
typedef bitset<8> BYTE;

class AESclass{
public:
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
void multVector(BYTE *vecEnt, BYTE *VecSal){
	VecSal[0]=((multiplicacion(vecEnt[0],BYTE (0x02)))^(multiplicacion(vecEnt[1],BYTE (0x03)))^(vecEnt[2])^(vecEnt[3]));
	VecSal[1]=((multiplicacion(vecEnt[1],BYTE (0x02)))^(multiplicacion(vecEnt[2],BYTE (0x03)))^(vecEnt[0])^(vecEnt[3]));
	VecSal[2]=((multiplicacion(vecEnt[2],BYTE (0x02)))^(multiplicacion(vecEnt[3],BYTE (0x03)))^(vecEnt[0])^(vecEnt[1]));
	VecSal[3]=((multiplicacion(vecEnt[3],BYTE (0x02)))^(multiplicacion(vecEnt[0],BYTE (0x03)))^(vecEnt[1])^(vecEnt[2]));
}
void mixColums(BYTE **mEnt,BYTE **mSal){
	for (int i = 0; i < 4; i++)
	{
		multVector(mEnt[0],mSal[0]);
	}
}
};