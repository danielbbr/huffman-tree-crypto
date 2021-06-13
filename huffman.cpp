#include<iostream>
#include<fstream>
#include <map>
#include<algorithm>


using namespace std;

//printa tabela de frequencia
void printar(map<char,int> tabela){
    map<char, int>::iterator it;
    for(it=tabela.begin(); it!=tabela.end(); ++it){
      cout << it->first << " => " << it->second << '\n';
   }
}
//gera tabela de frequencia
void gerar_tabela(map<char,int> &tabela){
    fstream my_file;
    my_file.open("teste_leitura.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		char ch;

		while (1) {
			my_file >> ch;
			if (my_file.eof())
				break;
            tabela[ch]++; 
			
		}

	}
	my_file.close();
}

class Nodo{
    public:
        int valor;
        char caracter;
        Nodo *esq;
        Nodo *dir;
};

class Arvore{
    public:
        Nodo raiz;
};
//função usada pra função de baixo
bool compare(const pair<char,int>& i, const pair<char, int>& j) {
  return i.second < j.second;
}
// retorna o menor elemento do map (tabela de frequencia da arvore de huffman)
pair<char,int> get_menor_valor(const map<char, int>& tabela){
    return *min_element(tabela.begin(), tabela.end(), compare);
}






int main(){
    map<char,int> tabela;
    
	gerar_tabela(tabela);
    
    pair<char, int> min = get_menor_valor(tabela);
    
}