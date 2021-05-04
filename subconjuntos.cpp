#include <iostream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define EPSILON -1
#define ACEPTACION 20

vector<unordered_map<int,int>> transiciones{
{{1,-1},{20,-1}},
{{2,-1},{14,-1}},
{{3,-1},{10,-1}},
{{4,-1},{9,-1}},
{{5,97}},
{{6,-1},{8,-1}},
{{7,98}},
{{8,-1},{6,-1}},
{{9,-1},{4,-1}},
{{13,-1}},
{{11,97}},
{{12,98}},
{{13,-1}},
{{19,-1}},
{{15,97}},
{{16,-1},{18,-1}},
{{17,98}},
{{18,-1},{16,-1}},
{{19,-1}},
{{20,-1},{1,-1}}
};

/*
vector<unordered_map<int,int>> transiciones{
{{0,0}},
{{2,-1},{9,-1}},
{{3,-1},{6,-1}},
{{4,'a'}},
{{5,'b'}},
{{8,-1}},
{{7,'c'}},
{{8,-1}},
{{2,-1},{9,-1}},
{{10,'a'}}
};
*/
/*
void printTablaEstados(vector<pair<char,vector<int>>> &tablaEstados){
	cout << "---------------------------------------" << endl;
	for(int i=0;i<tablaEstados.size();i++){
		cout << tablaEstados[i].first << " : ";
		for(int j=0;j<tablaEstados[i].second.size();j++)
			cout << tablaEstados[i].second[j] << '\t';
		cout << endl;
	}
	cout << "---------------------------------------" << endl;
}
*/
void aceptacion(vector<char> &nodosAceptacion){
	cout << "\nNodos con estado de aceptacion : {";
	for(auto acept: nodosAceptacion)
		cout<<acept<<" ";
	cout << "}" << endl;
}

void cerradura_e(vector<int> &nodosMover,vector<int> &nodosCerradura,vector<char> &nodosAceptacion,char estado){
	stack<char> pila;
	nodosCerradura.clear();

	if(nodosMover.empty())
		nodosMover.push_back(1);

	for(int i=0;i<nodosMover.size();i++) {
		pila.push(nodosMover[i]);
		nodosCerradura.push_back(nodosMover[i]);
		if(nodosMover[i] == ACEPTACION)
			nodosAceptacion.push_back(estado);
	}
	
	while(!pila.empty()) {
		int t = pila.top();
		pila.pop();
		for(auto tran: transiciones[t]){
			int i = 0;
			while(i<nodosCerradura.size() && tran.first!=nodosCerradura[i])
				i++;
			if(i == nodosCerradura.size()){
				if(tran.second==EPSILON){
					nodosCerradura.push_back(tran.first);
					if(tran.first == ACEPTACION)
						nodosAceptacion.push_back(estado);
					pila.push(tran.first);
				}
			}
		}
	}
	cout << "\n" << estado <<" : {|";
	for(int i=0;i<nodosMover.size();i++)
		cout<< nodosMover[i] << (i<nodosMover.size()-1? ",":"|,");

	for(int j=nodosMover.size();j<nodosCerradura.size();j++)
		cout << nodosCerradura[j] << (j<nodosCerradura.size()-1? ',':' ');
	cout << "}" << endl;
}

void print(vector<int> &nodosMover,char c,char estado, char estadoN){
	cout << " mover("<<estado<<","<< c <<") : {";
	for(int j=0;j<nodosMover.size();j++)
		cout << nodosMover[j] << (j<nodosMover.size()-1? ',':'}');
	cout << " =  " << estadoN << endl;
}

void printR(vector<int> &nodosMover,char c,char estado, char estadoN){
	cout << " mover("<<estado<<","<< c <<") : " << estadoN << endl;
}

void printP(vector<int> &nodosMover,char c,char estado, char estadoN){
	cout << " mover("<<estado<<","<< c <<") : {} = " << estadoN <<" (estado pozo)" << endl;
}

void copy(vector<int> &nodosCerradura,vector<pair<char,vector<int>>> &tablaEstados,char &estadoN){
	if(nodosCerradura.size()){
		tablaEstados.push_back(make_pair(estadoN,nodosCerradura));
	}else{
		nodosCerradura.push_back(-1);
		tablaEstados.push_back(make_pair(estadoN,nodosCerradura));
	}
	++estadoN;
}

void mover(vector<int> &nodosCerradura,vector<int> &nodosMover,int c){
	for(int i=0;i<nodosCerradura.size();i++){
		for(auto tran: transiciones[nodosCerradura[i]]){
			if(tran.second==c)
				nodosMover.push_back(tran.first);
		}
	}
	if(nodosMover.size() == 0) nodosMover.push_back(-1);
}

char no_marcado(vector<int> nodosMover,vector<pair<char,vector<int>>> tablaEstados){
	char estado = 'A';
	sort(nodosMover.begin(),nodosMover.end());
	for(int k=0;k<tablaEstados.size();k++) {
		if(tablaEstados[k].second.size() == 0) continue;
		sort(tablaEstados[k].second.begin(),tablaEstados[k].second.end());
		int i=0;
		for(int j=0;j<nodosMover.size();j++){
			if(nodosMover[j]==tablaEstados[k].second[j])
				i++;
		}
		if(i==nodosMover.size()) return tablaEstados[k].first;
		estado = tablaEstados[k].first;
	}
	return estado+1;
}

void imprimir(vector<pair<char,vector<int>>> tablaEstados,vector<int> nodosMover,vector<int> nodosCerradura){

	for(auto tran: tablaEstados){
		cout<<tran.first<<": ";
		for(auto nodo: tran.second){
			cout<< nodo <<" ";
		}
		cout<<endl;
	}

	cout<<"Nodos mover: ";
	for(auto mov: nodosMover)
		cout<<mov<<" ";
	cout<<endl;
	cout<<"Nodos cerradura: ";
	for(auto cer: nodosCerradura)
		cout<<cer<<" ";
	cout<<endl;
}

int main(){
	vector<int> nodosMover;
	vector<int> nodosCerradura;
	vector<char> nodosAceptacion;
	vector<pair<char,vector<int>>> tablaEstados;
	char estadoN = 'A';
	string alfabeto = "ab";

	//Cerradura de 0
	cerradura_e(nodosMover,nodosCerradura,nodosAceptacion,'A');
	//Se copia la cerradura de 0 a la tabla de estados
	copy(nodosCerradura,tablaEstados,estadoN);

	//Se recorre el alfabeto y se aplica la operacion 'mover'
	for(int i=0;i<alfabeto.size();i++){
		nodosMover.clear();
		mover(nodosCerradura,nodosMover,alfabeto[i]);
		if(nodosMover[0] != -1)
			print(nodosMover,alfabeto[i],'A',estadoN);
		else printP(nodosMover,alfabeto[i],'A',estadoN);
		copy(nodosMover,tablaEstados,estadoN);
	}
	//imprimir(tablaEstados,nodosMover,nodosCerradura);

	for(int k=1;k<tablaEstados.size();k++){
		nodosMover.clear();
		//Se copia el siguiente estado no procesado
		if(tablaEstados[k].second[0] == -1) continue;
		for(int j=0;j<tablaEstados[k].second.size();j++)
			nodosMover.push_back(tablaEstados[k].second[j]);
		//imprimir(tablaEstados,nodosMover,nodosCerradura);
		//Se le aplica la cerradura
		cerradura_e(nodosMover,nodosCerradura,nodosAceptacion,'A'+k);
		//Se recorre el alfabeto y se aplica la operacion 'mover'
		for(int i=0;i<alfabeto.size();i++){
			nodosMover.clear();
			mover(nodosCerradura,nodosMover,alfabeto[i]);
			//imprimir(tablaEstados,nodosMover,nodosCerradura);
			if(nodosMover[0] != -1){
				//Checa si el estado ya existe
				char est = no_marcado(nodosMover,tablaEstados);
				if(est == estadoN ){
					print(nodosMover,alfabeto[i],'A'+k,estadoN);
					copy(nodosMover,tablaEstados,estadoN);
				}else printR(nodosMover,alfabeto[i],'A'+k,est);
			}else{
				//printP(nodosMover,alfabeto[i],'A'+k,estadoN);
				char est = no_marcado(nodosMover,tablaEstados);
				if(est == estadoN ){
					print(nodosMover,alfabeto[i],'A'+k,estadoN);
					copy(nodosMover,tablaEstados,estadoN);
				}else printR(nodosMover,alfabeto[i],'A'+k,est);
			}
		}
	}

	aceptacion(nodosAceptacion);
	//printTablaEstados(tablaEstados);

	return 0;
}