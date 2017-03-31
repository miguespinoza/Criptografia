#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void toBinary(long c,char *a);

int main(int argc, char const *argv[])
{
	//123123123 456456456 789

	int c;
	long e,m,n;
	/*printf("base\n");
	scanf("%ld",&m);
	printf("%ld\n",m );
	printf("pot\n");
	scanf("%ld",&e);
	printf("%ld\n",e );
	printf("modulo\n");
	scanf("%ld",&n);
	printf("%ld\n",n );*/
	e=456456456;
	m=123123123;
	n=789;
	//double e=atoi(argv[2]);
	//double m=atoi(argv[1]);
	//double n=atoi(argv[3]);
	char *re=(char*)malloc(100);
	toBinary(e,re);
	printf("re %s\n",re );
	int len=strlen(re);
	if(re[len-1]==1)
		c=m;
	else
		c=1;
	for (int i = len-2; i >= 0; i--)
	{
		if(i==1)
			c=(c*m)%n;
		c=(c*c)%n;
	}
	printf("C: %d\n",c);
	
	
	return 0;
}


void toBinary(long c, char *b){
	char *a=(char*)malloc(100);
	int cont=1;
	a[0]='\0';
	while(c>0){
		
		
		a[cont-1]=(c%2)+'0';
		a[cont]='\0';
		
		c=(int)c/2;
		cont++;
	}
	char te;
	int len=strlen(a);
	b[5]='\0';
	printf("len%d\n",len );
	for (int i = 0; i <= len; i++)
	{
		//memcpy(&b[i],&a[len-i],1);
		b[i]=a[len-i];
		b[i+1]='\0';
		//printf("%c",b[i] );
		printf("%d",strlen(b));
	}
	b[len+1]='\0';
	printf("\n%s\n",b );
}

