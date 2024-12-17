#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

struct BCP{
	char nome[30];
	int idade;
	char nacionalidade[20];
	float altura;
	int peso;
	char modalidade [20];
	void imprime(){
	cout << nome << " "
		 << idade << " "
		 << nacionalidade << " "
		 << altura << " "
		 << peso << " "
		 << modalidade << endl;	
	}
};
bool lerumaunicalinha(ifstream& entrada, BCP& algumBCP){
	char virgula;
	return entrada.getline(algumBCP.nome,30,',')
			and (entrada >> algumBCP.idade >> virgula)
			and (entrada.getline(algumBCP.nacionalidade,20,','))
			and (entrada >> algumBCP.altura >> virgula)
			and (entrada >> algumBCP.peso >> virgula)
			and (entrada.getline(algumBCP.modalidade,20));
}
	
BCP* lerDados(int& numRegistros, int& capacidade){
	ifstream entrada("arquivoentrada.csv");
	if(not entrada){
		return NULL;
	}
	
	string descArquivo;
	
	getline(entrada,descArquivo);
	BCP* vetorBCP = new BCP [capacidade];
	
	BCP algumBCP;
	
			
	while(lerumaunicalinha(entrada, algumBCP)){
		if (numRegistros >= capacidade){
			capacidade += 20;
			BCP *novo = new BCP[capacidade];
			memcpy(novo, vetorBCP, numRegistros*sizeof(BCP));
			delete [] vetorBCP;
			vetorBCP = novo;
		}
		vetorBCP[numRegistros] = algumBCP;
		numRegistros ++;
	}
	return vetorBCP;
}

int main(){
		BCP* vetorBCP;
		int numRegistros = 0, capacidade = 50;
		vetorBCP = lerDados(numRegistros, capacidade);
		
		if (vetorBCP){
			ofstream gravaBinario ("arquivo.dat");
			
			for(int i = 0; i < numRegistros; i++){
				vetorBCP[i].imprime();
			}
			
		gravaBinario.write((char *) vetorBCP, numRegistros*sizeof(BCP));
		
		cout << "lendo binario" << endl << endl;	
				
		gravaBinario.close();
		ifstream leBinario("arquivo.dat");
		BCP umBCPQualquer;
		for ( int i=0; i<numRegistros; i++){
			leBinario.read((char *) &umBCPQualquer, sizeof(BCP));	
			umBCPQualquer.imprime();
		}
			
				
			delete [] vetorBCP;
		} else {
			cout << "nao foi possivel ler o arquivo" << endl;
		}
		
		
	
	return 0;
}
