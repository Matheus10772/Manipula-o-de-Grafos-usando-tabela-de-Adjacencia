#include "Origem.h"
int colocado = 0;

void RealocarMatriz(Grafo* _Grafo, unsigned int novoTamanho)
{
	int tamanhoAntigo = (*_Grafo).MatrizAdjacencia.size();
	(*_Grafo).MatrizAdjacencia.resize(novoTamanho, vector<unsigned int> (novoTamanho));
	for (int i = 0; i < tamanhoAntigo; i++) {
		(*_Grafo).MatrizAdjacencia[i].resize(novoTamanho);
	}
}

bool checkValoresValidos(char valoresValidos[], char valores[])
{
	int tamanho = (int)strlen(valores);
	int tamanho2 = (int)strlen(valoresValidos);
	for (int indice = 0; indice < tamanho; indice++) {
		bool controle = false;
		for (int indice2 = 0; indice2 < tamanho2; indice2++) {
			if (strcmp(&valores[indice],&valoresValidos[indice2]) == 0 && valores[indice] != '\n') {
				controle = true;
				break;
			}
		}
		if (!controle)
			return false;
	}
	return true;
}

vector<string> split_string(string str, const char* op) {
	vector<string> result;
	string rest = str, block;
	size_t operator_position = rest.find_first_of(op);
	while (operator_position != string::npos) {
		block = rest.substr(0, operator_position);
		rest = rest.substr(operator_position + 1);
		operator_position = rest.find_first_of(op);
		result.push_back(block);
	}

	if (rest.length() > 0)
		result.push_back(rest);

	return result;
}

vector<DadosDoArquivo> LerArquivo(string arqName)
{
	ifstream Arquivo (arqName);
	vector<DadosDoArquivo> arrayDeDadosConvertidos;
	char buffer[256];
	char caracteresValidos[] = {'1','2','3','4','5','6','7','8','9','0'};
	while (!Arquivo.eof())
	{
		DadosDoArquivo Dados;
		Arquivo.getline(buffer, 256);
		if (checkValoresValidos(caracteresValidos, buffer) && strlen(buffer) != 0) {
			vector<string> arrayDeDados = split_string(string(buffer), " ");
			unsigned int indice = 0;
			while (indice < arrayDeDados.size() - 1)
			{
				Dados.origem = stoi(arrayDeDados[indice]);
				indice++;
				Dados.destino = stoi(arrayDeDados[indice]);
				indice++;
				Dados.valor = stoi(arrayDeDados[indice]);
			}
			arrayDeDadosConvertidos.push_back(Dados);
		}
	}
	Arquivo.close();
	return arrayDeDadosConvertidos;
}

Grafo CriaGrafo(string Direcionado, unsigned int QuantidadeDeVertices, unsigned int QtdArestas)
{
	Grafo newGrafo;
	newGrafo.Direcionado = Direcionado;
	newGrafo.QuantidadeDeVertices = QuantidadeDeVertices;
	newGrafo.QuantidadeDeArestas = QtdArestas;	
	if (newGrafo.QuantidadeDeVertices != 0) {
		newGrafo.MatrizAdjacencia.resize(newGrafo.QuantidadeDeVertices, vector<unsigned int>(newGrafo.QuantidadeDeVertices,0));
	}
	else
	{
		newGrafo.MatrizAdjacencia.resize(1, vector<unsigned int>(1));
	}
	newGrafo.Vertices.resize(newGrafo.MatrizAdjacencia.size());
	return newGrafo;
}

vector<int> Sucessores(Grafo* _Grafo, unsigned int vertice)
{
	if ((*_Grafo).Direcionado == "Não direcionado") {
		cout << "Não é possível determinar os sucessores de um grafo não direcionado" << endl;
		return vector<int>(0);
	}
	else {
		return (*_Grafo).Vertices[vertice].Sucessores;
	}
}

vector<int> Antecessores(Grafo* _Grafo, unsigned int vertice)
{
	if ((*_Grafo).Direcionado == "Não direcionado") {
		cout << "Não é possível determinar os sucessores de um grafo não direcionado" << endl;
		return vector<int>(0);
	}
	else {
		return (*_Grafo).Vertices[vertice].Antecessores;
	}
}

void CriaAresta(Grafo* _Grafo, int origem, int destino, int valor)
{
	//(*_Grafo).QuantidadeDeArestas++;
	int teste = origem > destino ? origem : destino;
	if (((*_Grafo).MatrizAdjacencia.size()-1) <= teste) {
		int novoValor = (teste - (*_Grafo).MatrizAdjacencia.size()) + (*_Grafo).MatrizAdjacencia.size()+1;
		RealocarMatriz(_Grafo, novoValor);
		(*_Grafo).Vertices.resize(novoValor);
	}
	else if (((*_Grafo).MatrizAdjacencia.size()) == teste) {
		int novoValor = (*_Grafo).MatrizAdjacencia.size() + 1;
		RealocarMatriz(_Grafo, novoValor);
		(*_Grafo).Vertices.resize(novoValor);
	}
	if ((*_Grafo).Direcionado == "Direcionado") {
		(*_Grafo).MatrizAdjacencia[origem][destino] = valor;
		(*_Grafo).Vertices[origem].Sucessores.push_back(destino);
		(*_Grafo).Vertices[destino].Antecessores.push_back(origem);
	}
	else
	{
		(*_Grafo).MatrizAdjacencia[origem][destino] = valor;
		(*_Grafo).MatrizAdjacencia[destino][origem] = valor;
	}
	(*_Grafo).Vertices[origem].id = origem;
	(*_Grafo).Vertices[destino].id = destino;
	(*_Grafo).QuantidadeDeVertices = (*_Grafo).MatrizAdjacencia.size()-1;
}

int GrauDoVertice(Grafo* _Grafo, int vertice)
{
	vector<int> adj = adjacentes(_Grafo, vertice);
	cout << "Esse vértice possuí grau " + to_string(adj.size()) << endl;
	return adj.size();
}

vector<int> adjacentes(Grafo* _Grafo, int vertice)
{
	vector<int> adjacentes;
	for (unsigned int i = 0; i < (*_Grafo).MatrizAdjacencia.size(); i++) {
			if ((*_Grafo).MatrizAdjacencia[vertice][i] != 0) {
				adjacentes.push_back(i);
			}
	}
	return adjacentes;
}

float DensidadeDoGrafo(Grafo* _Grafo)
{
	float densidade;
	if ((*_Grafo).Direcionado == "Direcionado") {
		densidade = (float) (((float) (*_Grafo).QuantidadeDeArestas) / (((float)(*_Grafo).QuantidadeDeVertices) * (((float)(*_Grafo).QuantidadeDeVertices) - 1)));
	}
	else {
		densidade = (float)(2*((float)(*_Grafo).QuantidadeDeArestas) / (((float)(*_Grafo).QuantidadeDeVertices) * (((float)(*_Grafo).QuantidadeDeVertices) - 1)));
	}
	return densidade;
}

vector<float> Sumario(Grafo* _Grafo)
{
	vector<float> dados(4);
	cout << "Numero de Vertices = " + to_string((*_Grafo).QuantidadeDeVertices) << endl;
	dados.push_back((float)(*_Grafo).QuantidadeDeVertices);
	cout << "Numero de Arestas = " + to_string((*_Grafo).QuantidadeDeArestas) << endl;
	dados.push_back((float)(*_Grafo).QuantidadeDeArestas);
	float densidade = DensidadeDoGrafo(_Grafo);
	dados.push_back(densidade);
	cout << "Densidade do Grafo = " + to_string(densidade) << endl;
	return dados;
}

int main() {
	vector <DadosDoArquivo> DadosLidos = LerArquivo("exemplo_entrada.txt");
	unsigned int QuantidadeDeArestas = ((unsigned int) DadosLidos.size() - 1);
	Grafo novoGrafo = CriaGrafo("Direcionado", 0, QuantidadeDeArestas);
	for (auto indice = DadosLidos.begin(); indice != DadosLidos.end(); indice++) {
		CriaAresta(&novoGrafo, (*indice).origem, (*indice).destino, (*indice).valor);
	}
	Sumario(&novoGrafo);
	vector<int> sucessores = Sucessores(&novoGrafo, 4);
	vector<int> antecessores = Antecessores(&novoGrafo, 4);
	for (auto i = sucessores.begin(); i != sucessores.end(); i++) {
		cout << "sucessores " + to_string(*i) << endl;
	}
	for (auto i = antecessores.begin(); i != antecessores.end(); i++) {
		cout << "antecessores " + to_string(*i) << endl;
	}
	return 0;
} 
