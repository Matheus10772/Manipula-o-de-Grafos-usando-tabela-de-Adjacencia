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

void enfileirar(vector<Vertice*> &fileira, Vertice* item, int& MaxTamFileira) {
	fileira.push_back(item);
	MaxTamFileira += 1;
}

Vertice* desenfileirar(vector<Vertice*> &fileira, int& MaxTamFileira) {
	Vertice* item = fileira.front();
	for (int i = 0; i < MaxTamFileira; i++) {
		fileira[i] = fileira[i + 1];
	}
	fileira.pop_back();
	MaxTamFileira -= 1;
	/*if (MaxTamFileira < 0) {
		free(fileira);
		fileira = NULL;
	}*/
	return item;
}

bool BuscaEmLargura(vector <Vertice>& _Vertices, int verticeOrigem, int verticeDestino, string direcionado) {
	verticeOrigem = verticeOrigem - 1;
	verticeDestino = verticeDestino - 1;
	vector<Vertice*> fileira;
	Vertice* atual;
	int MaxTamFileira = 0;
	bool encontrou = false;
	_Vertices[verticeOrigem].cor = "cinza";
	_Vertices[verticeOrigem].distanciaOrigem = 0;
	enfileirar(fileira, &(_Vertices[verticeOrigem]), MaxTamFileira);
	if (direcionado == "Não direcionado") {
		do { //Enquanto a fila não está vazia
			atual = desenfileirar(fileira, MaxTamFileira); //Desenfileira
			if (atual->id == _Vertices[verticeDestino].id) {
				cout << "Encontrou" << endl;
				cout << "Vertice: " << atual->id << endl;
				encontrou = true;
				break;
			}
			int numDeAdjacencias = atual->Sucessores.size();
			for (int i = 0; i < numDeAdjacencias; i++) { //Percorre os adjacentes de u
				if (_Vertices[atual->Sucessores[i] - 1].cor == "branco") { //Testa se está na cor branca
					_Vertices[atual->Sucessores[i] - 1].cor == "cinza";//Define a cor como cinza
					_Vertices[atual->Sucessores[i] - 1].distanciaOrigem = atual->distanciaOrigem + 1;//Calcula a distância até v
					enfileirar(fileira, &(_Vertices[atual->Sucessores[i] - 1]), MaxTamFileira); //Coloca na fila
				}
			}
			atual->cor = "preto"; //Define a cor como preta
			cout << "Vertice " << atual->id << ": " << "cor = " << atual->cor << " distância = " << atual->distanciaOrigem << endl << endl;
		} while (MaxTamFileira > 0);
	}
	else 
	{
		do { //Enquanto a fila não está vazia
			atual = desenfileirar(fileira, MaxTamFileira); //Desenfileira
			if (atual->id == _Vertices[verticeDestino].id) {
				cout << "Encontrou" << endl;
				cout << "Vertice: " << atual->id << endl;
				encontrou = true;
				break;
			}
			int numDeAdjacencias = atual->Adjacentes.size();
			for (int i = 0; i < numDeAdjacencias; i++) { //Percorre os adjacentes de u
				if (_Vertices[atual->Adjacentes[i] - 1].cor == "branco") { //Testa se está na cor branca
					_Vertices[atual->Adjacentes[i] - 1].cor == "cinza";//Define a cor como cinza
					_Vertices[atual->Adjacentes[i] - 1].distanciaOrigem = atual->distanciaOrigem + 1;//Calcula a distância até v
					enfileirar(fileira, &(_Vertices[atual->Adjacentes[i] - 1]), MaxTamFileira); //Coloca na fila
				}
			}
			atual->cor = "preto"; //Define a cor como preta
			cout << "Vertice " << atual->id << ": " << "cor = " << atual->cor << " distância = " << atual->distanciaOrigem << endl << endl;
		} while (MaxTamFileira > 0);
	}
	return encontrou;
}

bool checarFConexa(Grafo* _CopyGrafo, int origem) {
	origem = origem - 1;
	vector <Vertice>* verticeInicial = new vector <Vertice>;
	verticeInicial->reserve(_CopyGrafo->Vertices.size());
	copy(_CopyGrafo->Vertices.begin(), _CopyGrafo->Vertices.end(), verticeInicial->begin());
	int contador = 0;
	bool isFConexa = false;

	vector <int>* fTransitivoDireto = new vector <int>;
	vector <int>* fTransitivoIndireto = new vector <int>;
	vector <int>* componenteCorrente = new vector <int>;
	vector <int>* nMais = new vector <int>(10);
	vector <int>* nMenos = new vector <int>(10);
	//vector <int>* nMaisS = new vector <int>(10); //N+(R+)-R+
	//vector <int>* nMenosS = new vector <int>(10); //N-(R-)-R-
	
	
	while (contador <= _CopyGrafo->QuantidadeDeVertices)
	{
		//verticeInicial->push_back(_CopyGrafo->Vertices[origem].id - 1);
		fTransitivoDireto->push_back(verticeInicial->front().id - 1);
		fTransitivoIndireto->push_back(verticeInicial->front().id - 1);

		for (int i = 0; i < fTransitivoDireto->size(); i++) {
			for (int j = 0; j < _CopyGrafo->Vertices[(*fTransitivoDireto)[i]].Sucessores.size(); j++) {
				bool control = false;
				for (int k = 0; k < fTransitivoDireto->size(); k++) {
					if (_CopyGrafo->Vertices[(*fTransitivoDireto)[i]].Sucessores[j] == (*fTransitivoDireto)[k]) {
						control = true;
						break;
					}
				}
				if(!control)
					nMais->push_back(_CopyGrafo->Vertices[(*fTransitivoDireto)[i]].Sucessores[j]);
			}
		}

		/*for (int i = 0; i < nMais->size(); i++) {
			bool control = false;
			for (int k = 0; k < fTransitivoDireto->size(); k++) {
				if ((*nMais)[i] == (*fTransitivoDireto)[k])
				{
					control = true;
					break;
				}
			}
			if (!control)
				nMaisS->push_back((*nMais)[i]);
		}*/

		for (int i = 0; i < fTransitivoIndireto->size(); i++) {
			for (int j = 0; j < _CopyGrafo->Vertices[(*fTransitivoIndireto)[i]].Antecessores.size(); j++) {
				bool control = false;
				for (int k = 0; k < fTransitivoIndireto->size(); k++) {
					if (_CopyGrafo->Vertices[(*fTransitivoIndireto)[i]].Antecessores[j] == (*fTransitivoIndireto)[k]) {
						control = true;
						break;
					}
				}
				if (!control)
					nMenos->push_back(_CopyGrafo->Vertices[(*fTransitivoIndireto)[i]].Antecessores[j]);
			}
		}

		/*for (int i = 0; i < nMenos->size(); i++) {
			bool control = false;
			for (int k = 0; k < fTransitivoIndireto->size(); k++) {
				if ((*nMenos)[i] == (*fTransitivoIndireto)[k])
				{
					control = true;
					break;
				}
			}
			if (!control)
				nMenosS->push_back((*nMenos)[i]);
		}*/

		while (!nMais->empty())
		{
			componenteCorrente->reserve(componenteCorrente->size() + nMais->size());
			componenteCorrente->insert(componenteCorrente->end(), nMais->begin(), nMais->end());
			fTransitivoDireto->reserve(fTransitivoDireto->size() + componenteCorrente->size());
			fTransitivoDireto->insert(fTransitivoDireto->end(), componenteCorrente->begin(), componenteCorrente->end());

			nMais->clear();
			for (int i = 0; i < fTransitivoDireto->size(); i++) {
				for (int j = 0; j < _CopyGrafo->Vertices[(*fTransitivoDireto)[i]].Sucessores.size(); j++) {
					bool control = false;
					for (int k = 0; k < fTransitivoDireto->size(); k++) {
						if (_CopyGrafo->Vertices[(*fTransitivoDireto)[i]].Sucessores[j] == (*fTransitivoDireto)[k]) {
							control = true;
							break;
						}
					}
					if (!control)
						nMais->push_back(_CopyGrafo->Vertices[(*fTransitivoDireto)[i]].Sucessores[j]);
				}
			}
			componenteCorrente->clear();
			componenteCorrente->resize(0);
		}

		while (!nMenos->empty())
		{
			componenteCorrente->reserve(componenteCorrente->size() + nMenos->size());
			componenteCorrente->insert(componenteCorrente->end(), nMenos->begin(), nMenos->end());
			fTransitivoIndireto->reserve(fTransitivoIndireto->size() + componenteCorrente->size());
			fTransitivoIndireto->insert(fTransitivoIndireto->end(), componenteCorrente->begin(), componenteCorrente->end());

			nMenos->clear();
			for (int i = 0; i < fTransitivoIndireto->size(); i++) {
				for (int j = 0; j < _CopyGrafo->Vertices[(*fTransitivoIndireto)[i]].Antecessores.size(); j++) {
					bool control = false;
					for (int k = 0; k < fTransitivoIndireto->size(); k++) {
						if (_CopyGrafo->Vertices[(*fTransitivoIndireto)[i]].Antecessores[j] == (*fTransitivoIndireto)[k]) {
							control = true;
							break;
						}
					}
					if (!control)
						nMenos->push_back(_CopyGrafo->Vertices[(*fTransitivoIndireto)[i]].Antecessores[j]);
				}
			}
			componenteCorrente->clear();
			componenteCorrente->resize(0);
		}

		for (int i = 0; i < fTransitivoDireto->size(); i++) {
			bool control = false;
			for (int j = 0; j < fTransitivoIndireto->size(); j++) {
				if ((*fTransitivoDireto)[i] == (*fTransitivoIndireto)[j]) {
					control = true;
					isFConexa = true;
					break;
				}
			}
			if (control) {
				for (int k = 0; k < verticeInicial->size(); k++) {
					if ((*fTransitivoDireto)[i] == (*verticeInicial)[k].id)
						verticeInicial->erase(verticeInicial->begin() + k);
				}
			}
		}

		fTransitivoDireto->clear();
		fTransitivoDireto->resize(0);
		fTransitivoIndireto->clear();
		fTransitivoIndireto->resize(0);

		contador++;
	}
	return isFConexa;
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

vector<vector<int>> LerArquivo(string arqName)
{
	std::ifstream Arquivo(arqName);
	vector<vector<int>> arrayDeDadosConvertidos;
	char buffer[256];
	string caracteresValidos = { "1234567890" };
	while (!Arquivo.eof())
	{
		vector<int> Dados;
		Arquivo.getline(buffer, 256);
		if (checkValoresValidos(caracteresValidos, buffer) && strlen(buffer) != 0) {
			vector<string> arrayDeDados = split_string(string(buffer), " ");
			unsigned int indice = 0;
			while (indice < arrayDeDados.size())
			{
				Dados.push_back(stoi(arrayDeDados[indice]));
				indice++;
			}
			arrayDeDadosConvertidos.push_back(Dados);
		}
	}
	Arquivo.close();
	return arrayDeDadosConvertidos;
}