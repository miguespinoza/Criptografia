#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int a,b,aux,cont=0;
	int qn,qn_;
	int rn,rn_1,rn_2,num,den;
	int *Q=(int*)malloc(sizeof(int));
	printf("Inverso multiplicativo\n");
	scanf("%d",&a);
	printf("Modulo\n");
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

	int  size=cont,GG=-1;
	int *X=(int*)malloc(sizeof(int)*size);
	int *Y=(int*)malloc(sizeof(int)*size);
	X[0]=1;
	X[1]=0;
	Y[0]=0;
	Y[1]=1;
	for(int i=2;i<=size;i++){
		//printf("%d\n",i );
		X[i]=GG*Q[i-2]*X[i-1]+X[i-2];
		Y[i]=GG*Q[i-2]*Y[i-1]+Y[i-2];	
		//printf("X%d= %d = %d * %d * %d + %d \n",i,X[i],GG,Q[i-1],X[i-1],X[i-2] );
		//printf("Y%d= %d = %d * %d * %d + %d \n",i,Y[i],GG,Q[i-1],Y[i-1],Y[i-2] );
		
	}
	
	printf("EXTENDIDO X: %d\n",a*X[size]+b*Y[size]);


	return 0;
}
