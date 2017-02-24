#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int a,b,aux,cont=0;
	int qn,qn_;
	int rn,rn_1,rn_2,num,den;
	int *Q=(int*)malloc(sizeof(int));
	printf("Introduce a\n");
	scanf("%d",&a);
	printf("Introduce b\n");
	scanf("%d",&b);
		//Cambiar en caso que a <b
	if (a<b){
		aux=a;
		a=b;
		b=aux;
	}
		//primera division
	num=a;	
	den=b;
	Q[cont]=num/den;
	rn=num % den;
	rn_2=a;
	rn_1=b;
	num=b;
	cont++;

		//divisiones subsecuentes
	while(rn!=0){
		Q=(int*)realloc(Q,cont+1*sizeof(int));
		den=rn;
		if(cont!=1)
			num=rn_1;	
		Q[cont]=(int)num/den;
		rn_2=rn_1;
		rn_1=rn;
		rn=num % den;
		cont++;
	}

	printf("gcd= %d\n",rn_1 );
	
	return 0;
}