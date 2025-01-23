#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;

struct sportlist{
	char nome[30];
	int idade;
	char nacionalidade[20];
	float altura;
	int peso;
	char modalidade [20];
	void imprime() {
        cout << "-----------------------------------------" << endl
			 << "Nome do Jogador: " << nome << endl
             << "Idade do Jogador: " << idade << " Anos" << endl
             << "Nacionalidade do Jogador: " << nacionalidade << endl
             << "Altura do Jogador: " << altura << " M" << endl
             << "Peso do Jogador: " << peso << " KG" << endl
             << "Modalidade do Jogador: " << modalidade << endl;
	}
};
bool lerumaunicalinha(ifstream& entrada, sportlist& algumsportlist){
	char virgula;
	return entrada.getline(algumsportlist.nome,30,',')
			and (entrada >> algumsportlist.idade >> virgula)
			and (entrada.getline(algumsportlist.nacionalidade,20,','))
			and (entrada >> algumsportlist.altura >> virgula)
			and (entrada >> algumsportlist.peso >> virgula)
			and (entrada.getline(algumsportlist.modalidade,20));
}
	
sportlist* lerDados(int& numRegistros, int& capacidade){
	ifstream entrada("arquivoentrada.csv");
	if(not entrada){
		return NULL;
	}
	
	string descArquivo;
	
	getline(entrada,descArquivo);
	sportlist* vetorsportlist = new sportlist [capacidade];
	
	sportlist algumsportlist;
	
			
	while(lerumaunicalinha(entrada, algumsportlist)){
		if (numRegistros >= capacidade){
			capacidade += 20;
			sportlist *novo = new sportlist[capacidade];
			memcpy(novo, vetorsportlist, numRegistros*sizeof(sportlist));
			delete [] vetorsportlist;
			vetorsportlist = novo;
		}
		vetorsportlist[numRegistros] = algumsportlist;
		numRegistros ++;
	}
	return vetorsportlist;
}

int main(){
		sportlist* vetorsportlist;
		int numRegistros = 0, capacidade = 50;
		vetorsportlist = lerDados(numRegistros, capacidade);
		
		if (vetorsportlist){
			ofstream gravaBinario ("arquivo.dat");
			
			for(int i = 0; i < numRegistros; i++){
				vetorsportlist[i].imprime();
			}
			
		gravaBinario.write((char *) vetorsportlist, numRegistros*sizeof(sportlist));
		
		cout << "lendo binario" << endl << endl;	
				
		gravaBinario.close();
		ifstream leBinario("arquivo.dat");
		sportlist umsportlistQualquer;
		for ( int i=0; i<numRegistros; i++){
			leBinario.read((char *) &umsportlistQualquer, sizeof(sportlist));	
			umsportlistQualquer.imprime();
		}
			
				
			delete [] vetorsportlist;
		} else {
			cout << "nao foi possivel ler o arquivo" << endl;
		}
		
		
	
	return 0;
}
