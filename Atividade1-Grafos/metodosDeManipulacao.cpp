#include "metodosDeManipulacao.h"

Grafo CriaGrafo(string Direcionado, unsigned int QuantidadeDeVertices, unsigned int QtdArestas)
{
	Grafo newGrafo;
	newGrafo.Direcionado = Direcionado;
	newGrafo.QuantidadeDeVertices = QuantidadeDeVertices;
	newGrafo.QuantidadeDeArestas = QtdArestas;
	if (newGrafo.QuantidadeDeVertices != 0) {
		newGrafo.MatrizAdjacencia.resize(newGrafo.QuantidadeDeVertices, vector<int>(newGrafo.QuantidadeDeVertices, 0));
		newGrafo.VerticePreDefinidos = true;
	}
	else
	{
		newGrafo.MatrizAdjacencia.resize(1, vector<int>(1, 0));
		newGrafo.VerticesAdicionados.resize(10,0);
		newGrafo.VerticePreDefinidos = false;
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
		return (*_Grafo).Vertices[vertice - 1].Sucessores;
	}
}

vector<int> Antecessores(Grafo* _Grafo, unsigned int vertice)
{
	if ((*_Grafo).Direcionado == "Não direcionado") {
		cout << "Não é possível determinar os sucessores de um grafo não direcionado" << endl;
		return vector<int>(0);
	}
	else {
		return (*_Grafo).Vertices[vertice - 1].Antecessores;
	}
}

bool checarExistenciaVertice(Grafo* _Grafo, int vertice)
{
	for (std::vector<int>::iterator i = (*_Grafo).VerticesAdicionados.begin(); i != (*_Grafo).VerticesAdicionados.end(); i++) {
		if (vertice == (*i))
			return true;
	}
	return false;
}

void CriaVertice(Grafo* _Grafo, int vertice)
{
	if (!(*_Grafo).VerticePreDefinidos) {
		if ((*_Grafo).QuantidadeDeVertices == (*_Grafo).VerticesAdicionados.size())
			(*_Grafo).VerticesAdicionados.resize((*_Grafo).VerticesAdicionados.size() * 2,0);
		if (!checarExistenciaVertice(_Grafo, vertice)) {
			(*_Grafo).QuantidadeDeVertices++;
			(*_Grafo).VerticesAdicionados.push_back(vertice);
		}
	}
}

void CriaAresta(Grafo* _Grafo, int origem, int destino, int valor)
{
	(*_Grafo).QuantidadeDeArestas++;
	int teste = origem > destino ? origem : destino;
	if (((*_Grafo).MatrizAdjacencia.size() - 1) < teste) {
		int novoValor = (teste - (*_Grafo).MatrizAdjacencia.size()) + (*_Grafo).MatrizAdjacencia.size();
		RealocarMatriz(_Grafo, novoValor);
		(*_Grafo).Vertices.resize(novoValor);
	}
	else if (((*_Grafo).MatrizAdjacencia.size()) == teste) {
		int novoValor = (*_Grafo).MatrizAdjacencia.size() + 1;
		RealocarMatriz(_Grafo, novoValor);
		(*_Grafo).Vertices.resize(novoValor);
	}
	if ((*_Grafo).Direcionado == "Direcionado") {
		(*_Grafo).MatrizAdjacencia[origem - 1][destino - 1] = valor;
		(*_Grafo).Vertices[origem - 1].Sucessores.push_back(destino);
		(*_Grafo).Vertices[destino - 1].Antecessores.push_back(origem);
	}
	else
	{
		(*_Grafo).MatrizAdjacencia[origem - 1][destino - 1] = valor;
		(*_Grafo).MatrizAdjacencia[destino - 1][origem - 1] = valor;
		(*_Grafo).Vertices[origem - 1].Adjacentes.push_back(destino);
		(*_Grafo).Vertices[destino - 1].Adjacentes.push_back(origem);
	}
	(*_Grafo).Vertices[origem - 1].id = origem;
	(*_Grafo).Vertices[destino - 1].id = destino;
	//(*_Grafo).QuantidadeDeVertices = (*_Grafo).MatrizAdjacencia.size();
	CriaVertice(_Grafo, origem);
	CriaVertice(_Grafo, destino);
}


vector<int> GrauDoVertice(Grafo* _Grafo, int vertice)
{
	vector<int> graus;
	vector<vector<int>> emissaoRecepcao = adjacentes(_Grafo, vertice);
	if ((*_Grafo).Direcionado == "Direcionado") {
		graus.push_back(emissaoRecepcao[0].size());
		graus.push_back(emissaoRecepcao[1].size());
		cout << "Grau de emissao: " + to_string(graus[0]) << endl;
		cout << "Grau de recepcao: " + to_string(graus[1]) << endl;
	}
	else {
		graus.push_back(emissaoRecepcao[0].size());
		cout << "Grau do vertice: " + to_string(graus[0]) << endl;
	}
	return graus;

}

vector<vector<int>> adjacentes(Grafo* _Grafo, int vertice)
{
	vector<vector<int>> adjacencia;
	if ((*_Grafo).Direcionado == "Direcionado") {
		adjacencia.push_back((*_Grafo).Vertices[vertice-1].Sucessores);
		adjacencia.push_back((*_Grafo).Vertices[vertice-1].Antecessores);
	}
	else {
		adjacencia.push_back((*_Grafo).Vertices[vertice-1].Adjacentes);
	}
	return adjacencia;
}

float DensidadeDoGrafo(Grafo* _Grafo)
{
	if ((*_Grafo).QuantidadeDeArestas == 0 || (*_Grafo).QuantidadeDeVertices == 0)
		return 0.0;
	float densidade;
	if ((*_Grafo).Direcionado == "Direcionado") {
		densidade = (float)(((float)(*_Grafo).QuantidadeDeArestas) / (((float)(*_Grafo).QuantidadeDeVertices) * (((float)(*_Grafo).QuantidadeDeVertices) - 1)));
	}
	else {
		densidade = (float)(2 * ((float)(*_Grafo).QuantidadeDeArestas) / (((float)(*_Grafo).QuantidadeDeVertices) * (((float)(*_Grafo).QuantidadeDeVertices) - 1)));
	}
	return densidade;
}

vector<vector<int>> MenorDistancia_FloydWarshall(Grafo* _Grafo)
{
	vector<vector<int>> matrizDistancia((*_Grafo).MatrizAdjacencia.size(), vector<int>((*_Grafo).MatrizAdjacencia.size(), 0)); //0 representa distancia infinita
	copy((*_Grafo).MatrizAdjacencia.begin(), (*_Grafo).MatrizAdjacencia.end(), matrizDistancia.begin());
	for (int j = 0; j < matrizDistancia.size(); j++) {
		for (int k = 0; k < matrizDistancia.size(); k++) {
			for (int l = 0; l < matrizDistancia.size(); l++) {
				int valor1 = matrizDistancia[k][j];
				int valor2 = matrizDistancia[j][l];
				if (k == l)
					matrizDistancia[k][l] = 0;
				else if (valor1 != 0 && valor2 != 0) {
					int soma = valor1 + valor2;
					if (soma < matrizDistancia[k][l] || matrizDistancia[k][l] == 0) {
						matrizDistancia[k][l] = soma;
					}
				}
			}
		}
	}
	return matrizDistancia;
}

vector<vector<int>> MaiorDistancia_FloydWarshall(Grafo* _Grafo)
{
	vector<vector<int>> matrizDistancia((*_Grafo).MatrizAdjacencia.size(), vector<int>((*_Grafo).MatrizAdjacencia.size(), 0)); //0 representa distancia infinita
	copy((*_Grafo).MatrizAdjacencia.begin(), (*_Grafo).MatrizAdjacencia.end(), matrizDistancia.begin());
	for (int j = 0; j < matrizDistancia.size(); j++) {
		for (int k = 0; k < matrizDistancia.size(); k++) {
			for (int l = 0; l < matrizDistancia.size(); l++) {
				int valor1 = matrizDistancia[k][j];
				int valor2 = matrizDistancia[j][l];
				if (k == l)
					matrizDistancia[k][l] = 0;
				else if (valor1 != 0 && valor2 != 0) {
					int soma = valor1 + valor2;
					if (soma > matrizDistancia[k][l] || matrizDistancia[k][l] == 0) {
						matrizDistancia[k][l] = soma;
					}
				}
			}
		}
	}
	return matrizDistancia;
}

vector<vector<int>> ExcentricidadeTodosOsVertices(Grafo* _Grafo)
{
	return MaiorDistancia_FloydWarshall(_Grafo);
}

int Raio(vector<vector<int>> MatrizExcentricidade)
{
	int raio = 0;
	bool achado = false;
	for (vector<vector<int>>::iterator i = MatrizExcentricidade.begin(); i != MatrizExcentricidade.end(); i++) {
		for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
			if ((*j) != 0) {
				raio = (*j);
				break;
				achado = true;
			}
		}
		if (achado)
			break;
	}
	for (vector<vector<int>>::iterator i = MatrizExcentricidade.begin(); i != MatrizExcentricidade.end(); i++) {
		for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
			if ((*j) < raio && (*j) != 0)
				raio = (*j);
		}
	}
	return raio;
}

vector<int> Centro(vector<vector<int>> MatrizExcentricidade, int raio)
{
	vector<int> verticesCentro;
	for (size_t i = 0; i < MatrizExcentricidade.size(); i++) {
		for (size_t j = 0; j < MatrizExcentricidade[i].size(); j++) {
			if (MatrizExcentricidade[i][j] == raio) 
				verticesCentro.push_back(i+1);
		}
	}
	return verticesCentro;
}

vector<int> Periferia(vector<vector<int>> MatrizExcentricidade, int diametro)
{
	vector<int> verticesPeriferia;
	for (size_t i = 0; i < MatrizExcentricidade.size(); i++) {
		for (size_t j = 0; j < MatrizExcentricidade[i].size(); j++) {
			if (MatrizExcentricidade[i][j] == diametro)
				verticesPeriferia.push_back(i);
		}
	}
	return verticesPeriferia;
}

int Diametro(vector<vector<int>> MatrizExcentricidade)
{
	int diametro = 0;
	for (vector<vector<int>>::iterator i = MatrizExcentricidade.begin(); i != MatrizExcentricidade.end(); i++) {
		for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
			if ((*j) > diametro)
				diametro = (*j);
		}
	}
	return diametro;
}

vector<int> centroide(vector<vector<int>> MatrizDistanciaMenores) {
	int centroide_ = 0;
	vector<int> vetorSomas;
	vector<int> vertices;
	vector<int> verticesFinal;
	for (vector<vector<int>>::iterator i = MatrizDistanciaMenores.begin(); i != MatrizDistanciaMenores.end(); i++) {
		long int soma = 0;
		for (vector<int>::iterator j = (*i).begin(); j != (*i).end(); j++) {
			soma += (*j);
		}
		if (soma != 0) {
			centroide_ = soma;
			break;
		}
	}

	for (size_t i = 0; i < MatrizDistanciaMenores.size(); i++) {
		long int soma = 0;
		for (size_t j = 0; j < MatrizDistanciaMenores[i].size(); j++) {
			soma += MatrizDistanciaMenores[i][j];
		}
		if (soma < centroide_) {
			centroide_ = soma;
			vetorSomas.push_back(centroide_);
			vertices.push_back(i);
		}
	}

	for (size_t i = 0; i < vetorSomas.size(); i++) {
		if (vetorSomas[i] == centroide_) 
			verticesFinal.push_back(vertices[i]);
	}
	return verticesFinal;
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

void RealocarMatriz(Grafo* _Grafo, unsigned int novoTamanho)
{
	int tamanhoAntigo = (*_Grafo).MatrizAdjacencia.size();
	(*_Grafo).MatrizAdjacencia.resize(novoTamanho, vector<int>(novoTamanho, 0));
	for (int i = 0; i < tamanhoAntigo; i++) {
		(*_Grafo).MatrizAdjacencia[i].resize(novoTamanho, 0);
	}
}

bool checkValoresValidos(string valoresValidos, char valores[])
{
	int tamanho = strlen(valores);
	int tamanho2 = valoresValidos.size();
	for (int indice = 0; indice < tamanho; indice++) {
		bool controle = false;

		if (valoresValidos.find(valores[indice]) != std::string::npos) {
			controle = true;
			break;
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
	std::ifstream Arquivo(arqName);
	vector<DadosDoArquivo> arrayDeDadosConvertidos;
	char buffer[256];
	string caracteresValidos = { "1234567890" };
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