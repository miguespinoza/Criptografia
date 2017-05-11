#include <iostream>
#include <bitset>
using namespace std;
typedef bitset<8> BYTE;

class AESclass{
private:
	BYTE ***roundKeys;
	BYTE **stateM;
	void initMemory();
	BYTE multiplicacion(BYTE a, BYTE b);
	void exchangeMatrix(BYTE **mDest,BYTE **mSource);
	BYTE SBOX(BYTE ent);
	void KeyExpansion();
	void subByteKey(BYTE *word);
	void wordRot(BYTE *word);
	BYTE is_box[16][16] =
	{	{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb },
		{ 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb },
		{ 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e },
		{ 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25 },
		{ 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92 },
		{ 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84 },
		{ 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06 },
		{ 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b },
		{ 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73 },
		{ 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e },
		{ 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b },
		{ 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4 },
		{ 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f },
		{ 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef },
		{ 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61 },
		{ 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d }};
	BYTE fs_box[16][16] =
	{	{ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 },
		{ 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 },
		{ 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 },
		{ 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 },
		{ 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 },
		{ 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf },
		{ 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 },
		{ 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 },
		{ 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 },
		{ 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb },
		{ 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 },
		{ 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 },
		{ 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a },
		{ 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e },
		{ 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf },
		{ 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }};
	BYTE rcon[10][4]=
	{	{0x01, 0x00,0x00,0x00},
		{0x02, 0x00,0x00,0x00},
		{0x04, 0x00,0x00,0x00},
		{0x08, 0x00,0x00,0x00},
		{0x10, 0x00,0x00,0x00},
		{0x20, 0x00,0x00,0x00},
		{0x40, 0x00,0x00,0x00},
		{0x80, 0x00,0x00,0x00},
		{0x1B, 0x00,0x00,0x00},
		{0x36, 0x00,0x00,0x00}};
public:
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
	AESclass(){
		initMemory();
	}
	std::string encrypt(std::string entrada, BYTE **clabe){
		setKey(clabe);
		std::string salida="";
		int longitud=entrada.size();
		cout<<"longitud de cadena"<<longitud%128<<endl;
		if (longitud%128!=0)
		{
			for (int i = 0; i < 128-longitud; ++i)
			{
				entrada+='_';
			}
		}
		int numCiclos=entrada.size()/128;
		cout<<"ciclos"<<entrada.size()<<endl;
		for (int ciclo = 0; ciclo < numCiclos; ++ciclo)
		{
			//create state matrix
			int cont=0;
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					stateM[i][j]=BYTE(entrada[cont]);
					cont++;
				}
			}
			printMatrix(stateM);
			//initial round
			addRoundKey(stateM,roundKeys[0]);
			//9rounds
			for (int ronda = 0; ronda < 9; ++ronda)
			{
				subByte(stateM);
				shiftRows(stateM);
				mixColums(stateM);
				addRoundKey(stateM,roundKeys[ronda+1]);
			}
			//final round
			subByte(stateM);
			shiftRows(stateM);
			addRoundKey(stateM,roundKeys[10]);
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					salida+=stateM[i][j].to_string();
				}
			}
		}
		
		
		return salida;
	}
	void encryptTEST(){
		BYTE **mEnt=(BYTE**)malloc(sizeof(BYTE)*4);
		BYTE **rKey=(BYTE**)malloc(sizeof(BYTE)*4);
		for (int i = 0; i < 4; ++i)
		{
			mEnt[i]=(BYTE*)malloc(sizeof(BYTE)*4);
			rKey[i]=(BYTE*)malloc(sizeof(BYTE)*4);
		}
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
		setKey(rKey);
	
		//create state matrix
		printf("----------------------input\n");
		stateM=mEnt;
		printMatrix(stateM);
		//initial round
		printf("----------------------1\n");
		addRoundKey(stateM,roundKeys[0]);
		printMatrix(stateM);
		//9rounds
		for (int ronda = 0; ronda < 9; ++ronda)
		{
			subByte(stateM);
			shiftRows(stateM);
			mixColums(stateM);
			addRoundKey(stateM,roundKeys[ronda+1]);
			printf("----------------------%d\n",ronda+2);
			printMatrix(stateM);
		}
		//final round
		subByte(stateM);
		shiftRows(stateM);
		addRoundKey(stateM,roundKeys[10]);

		printf("----------------------output\n");
		
		printMatrix(stateM);
	}
	/*void mixColums(BYTE **mEnt,BYTE **mSal);
	void addRoundKey(BYTE **mEnt,BYTE **mSal, BYTE **roundKey);
	void subByte(BYTE **mEnt, BYTE **mSal);
	void shiftRows(BYTE **mEnt, BYTE **mSal);*/
	void mixColums(BYTE **mEnt);
	void addRoundKey(BYTE **mEnt, BYTE **roundKey);
	void subByte(BYTE **mEnt);
	void shiftRows(BYTE **mEnt);
	void setKey(BYTE **sourcekey);

};

void AESclass:: initMemory(){
		
		roundKeys= (BYTE***)malloc(sizeof(BYTE)*11);
		stateM= (BYTE**)malloc(sizeof(BYTE)*4);
		for (int i = 0; i < 4; ++i)
		{
			stateM[i]= (BYTE*)malloc(sizeof(BYTE)*4);
		}
		for (int i = 0; i < 11; ++i)
		{
			roundKeys[i]=(BYTE**)malloc(sizeof(BYTE)*4);
			for (int j = 0; j < 4; ++j)
			{
				roundKeys[i][j]=(BYTE*)malloc(sizeof(BYTE)*4);
			}
		}
}
BYTE AESclass:: multiplicacion(BYTE a, BYTE b){
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
//void AESclass::mixColums(BYTE **mEnt,BYTE **mSal){
void AESclass::mixColums(BYTE **mEnt){
	for (int i = 0; i < 4; i++)
	{
		//multVector(mEnt[i],mEnt[i]);
		BYTE vec[4]={mEnt[i][0], mEnt[i][1], mEnt[i][2], mEnt[i][3]};
		mEnt[i][0]=((multiplicacion(vec[0],BYTE (0x02)))^(multiplicacion(vec[1],BYTE (0x03)))^(vec[2])^(vec[3]));
		mEnt[i][1]=((multiplicacion(vec[1],BYTE (0x02)))^(multiplicacion(vec[2],BYTE (0x03)))^(vec[0])^(vec[3]));
		mEnt[i][2]=((multiplicacion(vec[2],BYTE (0x02)))^(multiplicacion(vec[3],BYTE (0x03)))^(vec[0])^(vec[1]));
		mEnt[i][3]=((multiplicacion(vec[3],BYTE (0x02)))^(multiplicacion(vec[0],BYTE (0x03)))^(vec[1])^(vec[2]));
	}
}

void AESclass::addRoundKey(BYTE **mEnt, BYTE **roundKey){
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mEnt[i][j]=mEnt[i][j]^roundKey[i][j];
		}
	}
}

//void AESclass::subByte(BYTE **mEnt, BYTE **mSal){
void AESclass::subByte(BYTE **mEnt){
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mEnt[i][j]=SBOX(mEnt[i][j]);
		}
	}
}

BYTE AESclass::SBOX(BYTE ent){
	BYTE a(0b00001111);
	BYTE columna(ent&a);
	BYTE fila(ent>>4);
	BYTE map= fs_box[fila.to_ulong()][columna.to_ulong()];
	return map;
}

//void AESclass::shiftRows(BYTE **mEnt, BYTE **mSal){
void AESclass::shiftRows(BYTE **mEnt){
	short shift,au;
	BYTE buf[4];
	for (int fila = 0; fila < 4; ++fila)
	{
		shift=0+fila;
		au=0;
		buf[0]=mEnt[0][fila];
			buf[1]=mEnt[1][fila];
			buf[2]=mEnt[2][fila];
			buf[3]=mEnt[3][fila];
		for (int col = 0; col < 4; ++col)
		{	
			au=col+shift;
			if (au>=4)
			{
				au=au-4;
			}
			mEnt[col][fila]=buf[au];
		}
	}
}

void AESclass::exchangeMatrix(BYTE **mDest,BYTE **mSource){
	for (int i = 0; i < 4; ++i)
	{
		memcpy(mDest[i],mSource[i],sizeof(BYTE)*4);
	}
}

void AESclass::KeyExpansion(){
	BYTE *word=(BYTE*)malloc(sizeof(BYTE)*4);
	BYTE *word2=(BYTE*)malloc(sizeof(BYTE)*4);
	for (int matriz = 1; matriz < 11; ++matriz) //  llave original, matriz>0 round key
	{
		for (int columna = 0; columna < 4; ++columna)// recorre columnas
		{
			if (columna==0) //proceso de primer columna
			{
				memcpy(word,roundKeys[matriz-1][3-columna],sizeof(BYTE)*4);
				wordRot(word);	
				subByteKey(word);
				for (int fila = 0; fila < 4; ++fila)
				{
					roundKeys[matriz][columna][fila]=word[fila]^roundKeys[matriz-1][columna][fila]^rcon[matriz-1][fila];
				}
			}
			else //proceso de sigueintes columans 
			{
				memcpy(word,roundKeys[matriz-1][columna],sizeof(BYTE)*4);
				for (int fila = 0; fila < 4; ++fila)
				{
					roundKeys[matriz][columna][fila]=word[fila]^roundKeys[matriz][columna-1][fila];
				}	
			}	
		}
	}
}

void AESclass::subByteKey(BYTE *word){
	word[0]=SBOX(word[0]);
	word[1]=SBOX(word[1]);
	word[2]=SBOX(word[2]);
	word[3]=SBOX(word[3]);
}
void AESclass::wordRot(BYTE *word){
	BYTE aux;
	aux=word[0];
	word[0]=word[1];
	word[1]=word[2];
	word[2]=word[3];
	word[3]=aux;
}
void AESclass::setKey(BYTE **sourcekey){
	exchangeMatrix(roundKeys[0],sourcekey);
	KeyExpansion();
	/*printf("key\n");
	printMatrix(roundKeys[0]);
	printf("key 1\n");
	printMatrix(roundKeys[1]);
	printf("key 2\n");
	printMatrix(roundKeys[2]);
	printf("key 3\n");
	printMatrix(roundKeys[3]);
	printf("key 4\n");
	printMatrix(roundKeys[4]);
	printf("key 5\n");
	printMatrix(roundKeys[5]);
	printf("key 6\n");
	printMatrix(roundKeys[6]);
	printf("key 7\n");
	printMatrix(roundKeys[7]);
	printf("key 8\n");
	printMatrix(roundKeys[8]);
	printf("key 9\n");
	printMatrix(roundKeys[9]);
	printf("key 10\n");
	printMatrix(roundKeys[10]);*/
}
