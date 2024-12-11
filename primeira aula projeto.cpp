#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct BCP{
	string nome;
	int idade;
	string nacionalidade;
	float altura;
	int peso;
	string modalidade;
	void imprime(){
	cout << nome << " "
		 << idade << " "
		 << nacionalidade << " "
		 << altura << " "
		 << peso << " "
		 << modalidade << endl;	
	}
};
	
BCP* lerDados(int& numRegistros){
	ifstream entrada("arquivoentrada.csv");
	if(not entrada){
		return NULL;
	}
	
	string descArquivo;
	
	getline(entrada,descArquivo);
	entrada >> numRegistros;
	BCP* vetorBCP = new BCP [numRegistros];
	entrada.ignore();
	
	BCP algumBCP;
	char virgula;
			
	for(int i = 0; i < numRegistros; i++){	
		getline(entrada,algumBCP.nome,',');
		entrada >> algumBCP.idade >> virgula;
		getline(entrada,algumBCP.nacionalidade,',');
		entrada >> algumBCP.altura >> virgula;
		entrada >> algumBCP.peso >> virgula;
		getline(entrada,algumBCP.modalidade);
		vetorBCP[i] = algumBCP;
	}
	return vetorBCP;
}

int main(){
		BCP* vetorBCP;
		int numRegistros;
		vetorBCP = lerDados(numRegistros);
		
		if (vetorBCP){

			for(int i = 0; i < numRegistros; i++){
				vetorBCP[i].imprime();
			}
			
			delete [] vetorBCP;
		} else {
			cout << "nao foi possivel ler o arquivo" << endl;
		}
		
		
	
	return 0;
}
